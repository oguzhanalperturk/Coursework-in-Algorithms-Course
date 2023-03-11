/*
Oguzhan Alperturk 2315752

References:

https://www.geeksforgeeks.org/rabin-karp-algorithm-for-pattern-searching/

https://stackoverflow.com/questions/6417158/c-how-to-free-nodes-in-the-linked-list/6417182  (freeList function)

*/



#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct numbers{ /*For finding the most frequent AOI*/
	char no;
	int count;
};
struct indexnode{
	int index;
	struct indexnode *next;
};
struct IndexRecord{
 	struct indexnode *head;
 	struct indexnode *tail;
 	int size;
};
typedef struct IndexRecord *indexlist;

struct node{
	char scanpath[101];
	struct node *next;
};

struct ListRecord{
 	struct node *head;
 	struct node *tail;
 	int size;
};
typedef struct ListRecord *List;




List createScanpathList(char name[25]); /*Create lists with dummy node at the beginning of the list*/

void printlist(List temp);

indexlist RabinKarp(char pat[], char txt[], int q);

void printbrackets(char *pattern,List l);

void searchPattern(char *pattern,List peoplewithautism,List peoplewithoutautism);

void freeList(struct node* head);



int main(){
	
	List peoplewithautism,peoplewithoutautism;
	char filename1[40];
	char filename2[40];
	char pattern[40];
	
	printf("Enter the file name for people with autism:");
	scanf("%s",filename1);
	printf("Enter the file name for people with autism:");
	scanf("%s",filename2);
	printf("Enter the pattern:");
	scanf("%s",pattern);
	
	
	peoplewithautism = createScanpathList("peoplewithautism.txt");
	peoplewithoutautism = createScanpathList("peoplewithoutautism.txt");
	
	searchPattern(pattern,peoplewithautism,peoplewithoutautism);
	
	freeList(peoplewithautism->head);
	freeList(peoplewithoutautism->head);
	
	return 0;
}




List createScanpathList(char name[25]){
	
	List temp;
	struct node *iter;
	temp = (List )malloc(sizeof(List));
	temp->head = (struct node *)malloc(sizeof(struct node));
	temp->tail = temp->head;
	temp->size = 0;
	iter = temp->head;
	
	FILE *ffile;
	char str[100];
	char line[100];
	char *piece;
	ffile = fopen(name,"r");
	int i = 0;
 
while(1){
	
	if(fgets(str,sizeof(str),ffile) == NULL){
		iter->next = NULL;
		temp->tail = iter;
		break;
	}
	else{
		iter->next = (struct node *)malloc(sizeof(struct node));
		iter = iter->next;
		
		strcpy(line,strtok(str,"\n"));
		strcpy(iter->scanpath,line);
	}
    temp->size ++;	
}
	fclose(ffile);

	return temp;
}


void printlist(List temp){
	
	struct node *iter;
	iter = temp->head;
	iter = iter->next;
	
	while(iter != NULL){

		printf("scanpath: %s\n",iter->scanpath);
		iter = iter->next;
		}
}


indexlist RabinKarp(char pat[], char txt[], int q){
	
	indexlist indexes = (indexlist )malloc(sizeof(indexlist));
	indexes->head = (struct indexnode *)malloc(sizeof(struct indexnode));
	indexes->tail = indexes->head;
	indexes->tail->next = NULL;
	indexes->size = 0;
	struct indexnode *newnode;
	
	
	int d = 10;
	int M = strlen(pat);
    int N = strlen(txt);
    int i, j;
    int p = 0; // hash value for pattern
    int t = 0; // hash value for txt
    int h = 1;
 
    // The value of h would be "pow(d, M-1)%q"
    for (i = 0; i < M-1; i++)
        h = (h*d)%q;
 
    // Calculate the hash value of pattern and first
    // window of text
    for (i = 0; i < M; i++)
    {
        p = (d*p + pat[i])%q;
        t = (d*t + txt[i])%q;
    }
 
    // Slide the pattern over text one by one
    for (i = 0; i <= N - M; i++)
    {
 
        // Check the hash values of current window of text
        // and pattern. If the hash values match then only
        // check for characters on by one
        if ( p == t )
        {
            /* Check for characters one by one */
            for (j = 0; j < M; j++)
            {
                if (txt[i+j] != pat[j])
                    break;
            }
 
            // if p == t and pat[0...M-1] = txt[i, i+1, ...i+M-1]
            if (j == M){
				newnode = (struct indexnode *)malloc(sizeof(struct indexnode));
				newnode->index = i;
				newnode->next = NULL;
				indexes->tail->next = newnode;
				indexes->tail = newnode;
            	indexes->size++;
   	     	}
        }
 
        // Calculate hash value for next window of text: Remove
        // leading digit, add trailing digit
        if ( i < N-M )
        {
            t = (d*(t - txt[i]*h) + txt[i+M])%q;
 
            // We might get negative value of t, converting it
            // to positive
            if (t < 0)
            t = (t + q);
        }
    }
    return indexes;
}


void searchPattern(char *pattern,List peoplewithautism,List peoplewithoutautism){
	
	
	printf("Detected patterns for people with autism:\n");
	printbrackets(pattern,peoplewithautism);

	printf("Detected patterns for people without autism:\n");
	printbrackets(pattern,peoplewithoutautism);
}


void printbrackets(char *pattern,List l){
	struct numbers nums[10];
	nums[0].no = '0';
	nums[1].no = '1';
	nums[2].no = '2';
	nums[3].no = '3';
	nums[4].no = '4';
	nums[5].no = '5';
	nums[6].no = '6';
	nums[7].no = '7';
	nums[8].no = '8';
	nums[9].no = '9';
	int i,j,lengthscanpath,lengthpattern,flag = 0,indexstorage=0,patternnum=0,counter = 1;
	for(i=0;i<10;i++){
		nums[i].count = 0;
	}
	lengthpattern = strlen(pattern);
	indexlist indexes;
	struct indexnode *iterindex;
	struct node *iter;
	
	for(iter = l->head->next;iter!=NULL;iter=iter->next){
		indexes = RabinKarp(pattern,iter->scanpath,11);
		if(indexes->head->next != NULL){
			printf("%d. ",counter);
			counter++;
			for(iterindex = indexes->head->next;iterindex!=NULL;iterindex=iterindex->next){
				lengthscanpath = strlen(iter->scanpath);
				for(i=indexstorage;i<=lengthscanpath;i++){
					if(i == iterindex->index -1){
						printf("%c",iter->scanpath[i]);
						printf("[");
						for(j=0;j<10;j++){
							if(iter->scanpath[i] == nums[j].no){
								nums[j].count++;
								break;
							}
						}
						flag = 0;
					}
					else if(iterindex->index == 0 && i==0){
						printf("[");
						printf("%c",iter->scanpath[i]);
						flag = 0;
					}
					else if(i == iterindex->index + lengthpattern){
						printf("]");
						patternnum++;
						if(iterindex->next != NULL){
							if(iterindex->index + lengthpattern == iterindex->next->index){
								printf("[");
								for(j=0;j<10;j++){
									if(iter->scanpath[i-1] == nums[j].no){
										nums[j].count++;
										break;
									}
								}
							}
						}
						printf("%c",iter->scanpath[i]);
						flag = 1;
						indexstorage = i+1;
						break;
					}
					else{
						printf("%c",iter->scanpath[i]);
					}
				}
			}

			for(i = indexstorage;i<lengthscanpath;i++){
				printf("%c",iter->scanpath[i]);
			}

			printf("\n");
		}
		indexstorage = 0;
	}
	int maxnum = 0;
	char maxno;
	int control = 0; /* For finding how many numbers have maximum count*/
	
	
	if(counter == 1){
		printf("None\n");
	}
	else{
		printf("%d pattern detected in %d scanpaths\n",patternnum,l->size);
		for(j=0;j<10;j++){
			if(nums[j].count > maxnum){
				maxnum= nums[j].count;
			}
		}
		for(i=0;i<10;i++){
			if(nums[i].count==maxnum){
				control++;
			}
		}
		printf("The most frequent AOI before the pattern ");
		if(control > 1){
			printf("are ");
			for(j=0;j<10;j++){
				if(nums[j].count == maxnum){
					printf("%c ",nums[j].no);
				}
			}
		}
		else{
			for(j = 0;j<10;j++){
				if(nums[j].count >= maxnum){
					maxnum = nums[j].count;
					maxno = nums[j].no;
					printf("is %c\n\n",maxno);
				}
			}
		}
	}
}


void freeList(struct node* head){
   struct node* tmp;

   while (head != NULL)
    {
       tmp = head;
       head = head->next;
       free(tmp);
    }

}


