/*
Oguzhan Alperturk 2315752

*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>


struct Student{
	int isempty; /*1->occupied 0->empty*/
	char id[4];
	char name[40];
	char dept[4];
};

int findnextprimeno(int num);

void AddStudent(struct Student* hashtable,struct Student newstudent,int size,int choice);

int SearchStudent(struct Student *hashtable,int size,char *id,int choice,int printornot); 

/* printornot variable means, if I am searching for a student info then it prints its information
   But, if I want to know only that if the student is in the hash table or not
   then the function do not print anything only return the information.(beginning of the insert operation) 
   1-> student is in the hash table
   0-> student is not in the hash table */
	
void print(struct Student* hashtable,int size);




int main(){
	struct Student *hashtable;
	struct Student *newtable;
	hashtable = (struct Student *)malloc(sizeof(struct Student) * 11);
	struct Student newstudent; 
	int addressingchoice,funcchoice,i,size = 11,oldsize;
	char id[4];
	float studentno = 0,loadfactor;

	for(i=0;i<11;i++){
		hashtable[i].isempty = 0;
	}
	
	printf("(1)Double hashing\n(2)Quadratic probing\n\nEnter your choice: ");
	scanf("%d",&addressingchoice);
	
	while(1){
		printf("\n\n(1)Add a student\n");
		printf("(2)Search a student\n");
		printf("(3)Print table\n");
		printf("(4)Exit\n");
		printf("Enter the command: ");
		scanf("%d",&funcchoice);
		if(funcchoice == 1){
				
			printf("\nEnter unique identifier: ");
			scanf("%s",newstudent.id);
			
			if(SearchStudent(hashtable,size,newstudent.id,addressingchoice,0) == 1){
				printf("ID should be unique!\n\n");
			}
			else{
				printf("Enter Name: ");
				fflush(stdin);
				scanf("%[^\n]s",newstudent.name);
				printf("Enter Department: ");
				scanf("%s",newstudent.dept);
				
				
				
				AddStudent(hashtable,newstudent,size,addressingchoice);
				studentno++;
				
				loadfactor = studentno / size;
				if(loadfactor > 0.5){  /*Rehashing*/
					oldsize = size;
					size *= 2;
					size = findnextprimeno(size);
					newtable = (struct Student *)malloc(sizeof(struct Student) * size);
					for(i = 0;i<size;i++){
						newtable[i].isempty = 0;
					}
					for(i=0;i<oldsize;i++){
						if(hashtable[i].isempty == 1){
							strcpy(newstudent.id,hashtable[i].id);
							strcpy(newstudent.name,hashtable[i].name);
							strcpy(newstudent.dept,hashtable[i].dept);
							AddStudent(newtable,newstudent,size,addressingchoice);
						}
					}
					free(hashtable);
					hashtable = newtable;	
				}
			}
			
		}
		else if(funcchoice == 2){
			printf("Enter unique identifier: ");
			scanf("%s",id);
			SearchStudent(hashtable,size,id,addressingchoice,1);
			
		}
		else if(funcchoice == 3){
			print(hashtable,size);
		}
		else if(funcchoice == 4){
			printf("Goodbye\n");
			break;
		}
		else{
			printf("Enter a valid command!\n");
		}
	}
	
	

	
	return 0;
}




int findnextprimeno(int num){
	
	int i,j=num+1,flag = 0;
	
	while(1){
		for(i=2;i<j;i++){
			if(j % i == 0){
				flag++;
				break;
			}
		}
		if(flag == 0){
			return j;
		}
		j++;
		flag = 0;
	}	
}


void AddStudent(struct Student* hashtable,struct Student newstudent,int size,int choice){
	int ascivalue,value1,value2,key,h1,h2,index,i;
	value1 = newstudent.id[1] - '0';
	value2 = newstudent.id[2] - '0';
	ascivalue = newstudent.id[0];
	key = ascivalue - 65 + value1 + value2;
	h1 = (2*key) % size;
	
	if(choice == 1){
		h2 = 7-(key % 7);
		for(i=0;i<size;i++){
			index = (h1 + h2*i) % size;
			if(hashtable[index].isempty == 0){
				strcpy(hashtable[index].id,newstudent.id);
				strcpy(hashtable[index].dept,newstudent.dept);
				strcpy(hashtable[index].name,newstudent.name);
				hashtable[index].isempty = 1;
				break;
			}
		}
	}
	else if(choice == 2){
		for(i=0;i<size;i++){
			index = h1 + (i*i);
			if(hashtable[index].isempty == 0){
				strcpy(hashtable[index].id,newstudent.id);
				strcpy(hashtable[index].dept,newstudent.dept);
				strcpy(hashtable[index].name,newstudent.name);
				hashtable[index].isempty = 1;
				break;
			}
		}
	}
	
	printf("%s has been registered.\n",newstudent.name);
}


int SearchStudent(struct Student *hashtable,int size,char *id,int choice,int printornot){
	int ascivalue,value1,value2,key,h1,h2,index,i;
	value1 = id[1] - '0';
	value2 = id[2] - '0';
	ascivalue = id[0];
	key = ascivalue - 65 + value1 + value2;
	h1 = (2*key) % size;
	
	if(choice == 1){
		h2 = 7-(key % 7);
		for(i=0;i<size;i++){
			index = (h1 + h2*i) % size;
			if(hashtable[index].isempty == 1){
				if(strcmp(hashtable[index].id,id) == 0){
					if(printornot == 1){
						printf("\n\nStudent id: %s\n",hashtable[index].id);
						printf("Student name: %s\n",hashtable[index].name);
						printf("Student department: %s\n",hashtable[index].dept);
					}
					return 1;
				}
			}
			else{
				if(printornot == 1){
					printf("\n\nStudent is not found!!\n");
				}
				return 0;
			}
		}
	}
	else if(choice == 2){
		for(i=0;i<size;i++){
			index = h1 + (i*i);
			if(hashtable[index].isempty == 1){
				if(strcmp(hashtable[index].id,id) == 0){
					if(printornot == 1){
						printf("\n\nStudent id: %s\n",hashtable[index].id);
						printf("Student name: %s\n",hashtable[index].name);
						printf("Student department: %s\n",hashtable[index].dept);
					}
					return 1;
				}
			}
			else{
				if(printornot == 1){
					printf("\n\nStudent is not found!!\n");
				}
				return 0;
			}
		}
	}
}


void print(struct Student* hashtable,int size){
	int i,j,length;
	printf("Index     ID           Name                     Department\n");
	
	for(i=0;i<size;i++){
		if(hashtable[i].isempty == 1){
			printf("%d         %s          %s",i,hashtable[i].id,hashtable[i].name);
			length = 25 - strlen(hashtable[i].name);
			for(j = 0;j<length;j++){
				printf(" ");
			}
			printf("%s\n",hashtable[i].dept);	
		}
		else{
			printf("%d\n",i);
		}
	}
}




