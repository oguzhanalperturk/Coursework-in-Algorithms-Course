/*
Oguzhan Alperturk 2315752

References :

https://www.geeksforgeeks.org/longest-common-subsequence-dp-4/

*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Coordinate{
	int x;
	int y;
};

struct AoisCoord{
	char elementname[2];
	struct Coordinate topleft;
	struct Coordinate topright;
	struct Coordinate bottomleft;
	struct Coordinate bottomright;
};

struct Aoislist{
	struct AoisCoord *aois;
	int size;
};

struct FixationInfo{
	int id;
	struct Coordinate fixationcoord;
	int duration;
};

struct Fixationlist{
	struct FixationInfo *fixation;
	int size;
};

struct Person{
	int id;
	char scanpath[101];
};

struct Personlist{
	struct Person *people;
	int size;
};

struct Node {
	int id;
    char scanpath[101];
    int weight;
    struct Node* next;
};

struct Graph {
    struct Node* list;
    int size;
};






void printAoislist(struct Aoislist a);
	
struct Aoislist InitializeAoisCoord(char filename[25]);	
	
struct Fixationlist InitializeFixations(char filename[25]);

void printFixationlist(struct Fixationlist f);

int IsinsideRectangle(struct Coordinate point,struct Coordinate topleft,struct Coordinate bottomright); /* to find given coordinate is in the rectangle or not 1->yes, 0-> no */

struct Personlist InitializePeople(struct Aoislist a,struct Fixationlist f);

void printpeople(struct Personlist p);

void printgraph(struct Graph g);

struct Graph createVertices(char aoisfilename[20], char fixationsfilename[20]);

int max(int a, int b);

int lcscalc( char *X, char *Y, int m, int n );

struct Graph createEdges(struct Graph g);

void printGraph(struct Graph g);





int main(){
	
	struct Graph g;
	g = createVertices("aois.txt","fixations.txt");
	g = createEdges(g);

	printGraph(g);
	
	
	
	
	
	
	
	
	
	
	return 0;
}




struct Aoislist InitializeAoisCoord(char filename[25]){
	
	struct Aoislist c;
	c.aois = (struct AoisCoord*)malloc(sizeof(struct AoisCoord));
	c.size = 0;
	
	FILE *ffile;
	char str[100];
	char line[100];
	char *piece;
	ffile = fopen(filename,"r");
	
	int i = 0,elementno = -1,topleftx,width,toplefty,height;
 
	while(1){
		if(fgets(str,sizeof(str),ffile) == NULL){
			break;
		}
		else{	
			c.size++;
			c.aois = (struct AoisCoord*)realloc(c.aois,sizeof(struct AoisCoord)*c.size);	
			elementno++;
			strcpy(line,strtok(str," "));
			strcpy(c.aois[elementno].elementname,line);
			i=0;
			while(1){
				if(i==0){
					piece = strtok(NULL, " ");
					topleftx = atoi(piece);
						if(piece == NULL){
							break;
					}	}
					else if(i==1){
					piece = strtok(NULL, " ");
					width = atoi(piece);
						if(piece == NULL){
							break;
					}	}
					else if(i==2){
					piece = strtok(NULL, " ");
					toplefty = atoi(piece);
						if(piece == NULL){
							break;
					}	}
					else if(i==3){
					piece = strtok(NULL, " ");
					height = atoi(piece);
						if(piece == NULL){
							break;
					}
					c.aois[elementno].topleft.x = topleftx;
					c.aois[elementno].topleft.y =toplefty;
					c.aois[elementno].topright.x = width + topleftx;
					c.aois[elementno].topright.y = toplefty;
					c.aois[elementno].bottomleft.x = topleftx;
					c.aois[elementno].bottomleft.y = toplefty + height;
					c.aois[elementno].bottomright.x =topleftx + width;
					c.aois[elementno].bottomright.y =toplefty + height;
					}
				else break;
				
				i++;
			}	
		}
	}
	fclose(ffile);
	return c;
}


void printAoislist(struct Aoislist a){
	int i;
	for(i=0;i<a.size;i++){
		printf("%s\n",a.aois[i].elementname);
		printf("(%d,%d)\n",a.aois[i].topleft.x,a.aois[i].topleft.y);
		printf("(%d,%d)\n",a.aois[i].topleft.x,a.aois[i].topright.y);
		printf("(%d,%d)\n",a.aois[i].topleft.x,a.aois[i].bottomleft.y);
		printf("(%d,%d)\n\n\n",a.aois[i].topleft.x,a.aois[i].bottomright.y);
	}
}


struct Fixationlist InitializeFixations(char filename[25]){
	
	struct Fixationlist c;
	c.fixation = (struct FixationInfo*)malloc(sizeof(struct FixationInfo));
	c.size = 0;
	
	FILE *ffile;
	char str[100];
	char line[100];
	char *piece;
	ffile = fopen(filename,"r");
	
	int i = 0,elementno = -1;
 
	while(1){
		if(fgets(str,sizeof(str),ffile) == NULL){
			break;
		}
		else{	
			c.size++;
			c.fixation = (struct FixationInfo*)realloc(c.fixation,sizeof(struct FixationInfo)*c.size);	
			elementno++;
			strcpy(line,strtok(str," "));
			c.fixation[elementno].id = atoi(line);
			i=0;
			while(1){
				if(i==0){
					piece = strtok(NULL, " ");
					c.fixation[elementno].fixationcoord.x = atoi(piece);
						if(piece == NULL){
							break;
					}	}
					else if(i==1){
					piece = strtok(NULL, " ");
					c.fixation[elementno].fixationcoord.y = atoi(piece);
						if(piece == NULL){
							break;
					}	}
					else if(i==2){
					piece = strtok(NULL, " ");
					c.fixation[elementno].duration = atoi(piece);
						if(piece == NULL){
							break;
					}	}
				else break;
				
				i++;
			}	
		}
	}
	fclose(ffile);
	return c;
}


void printFixationlist(struct Fixationlist f){
	int i;
	for(i=0;i<f.size;i++){
		printf("%d\n",f.fixation[i].id);
		printf("(%d,%d)\n",f.fixation[i].fixationcoord.x,f.fixation[i].fixationcoord.y);
		printf("%d\n\n\n",f.fixation[i].duration);
	}
}


int IsinsideRectangle(struct Coordinate point,struct Coordinate topleft,struct Coordinate bottomright){
	if(point.x >= topleft.x && point.x <= bottomright.x){
		if(point.y >= topleft.y && point.y <= bottomright.y){
			return 1;
		}
	}
	return 0;
}



struct Personlist InitializePeople(struct Aoislist a,struct Fixationlist f){
	struct Personlist p;
	p.size = 0;
	int i = 0,j = 0,id = 1,personcount = -1,pointcheck,startingzerocheck = 0;
	char scanpath[101];
	strcpy(scanpath,"");

	
	for(i=0;i<f.size+1;i++){
		if((f.fixation[i].id == 0 && startingzerocheck != 0) || i == f.size){
			p.size ++;
			p.people = (struct Person*)realloc(p.people,sizeof(struct Person)*p.size);
			personcount++;
			strcpy(p.people[personcount].scanpath,scanpath);
			p.people[personcount].id = id;
			id++; 
			strcpy(scanpath,"");
		}
		for(j=0;j<a.size;j++){
			pointcheck = IsinsideRectangle(f.fixation[i].fixationcoord,a.aois[j].topleft,a.aois[j].bottomright);
			printf("",pointcheck);
			if(pointcheck == 1){
				strcat(scanpath,a.aois[j].elementname);
			}
		}
		startingzerocheck++;
	}
	
	free(a.aois);
	free(f.fixation);
	return p;
}


void printpeople(struct Personlist p){
	int i;
	for(i=0;i<p.size;i++){
		printf("%d : %s\n\n",p.people[i].id,p.people[i].scanpath);
	}
}



struct Graph createVertices(char aoisfilename[20], char fixationsfilename[20]){
	int i;
	struct Aoislist a;
	a = InitializeAoisCoord(aoisfilename);
	
	struct Fixationlist f;
	f = InitializeFixations(fixationsfilename);
	
	struct Personlist p;
	p = InitializePeople(a,f);
	
	struct Graph g;
	g.size = p.size;

	g.list = (struct Node*)calloc(0,p.size * sizeof(struct Node));
	
	for(i=0;i<g.size;i++){
		strcpy(g.list[i].scanpath,p.people[i].scanpath);
		g.list[i].next = NULL;	
		g.list[i].id = i+1;
	}	
	return g;
}


void printgraph(struct Graph g){
	int i;
	for(i=0;i<g.size;i++){
		printf("%d:%s\n\n",i,g.list[i].scanpath);
	}
}


int max(int a, int b)
{
    if(a>b){
    	return a;
	}
	else{
		return b;
	}
}

int lcscalc( char *X, char *Y, int m, int n ){
	int L[m+1][n+1];
	int i, j;
	 
	for (i=0; i<=m; i++){
	    for (j=0; j<=n; j++){
	    if (i == 0 || j == 0)
	        L[i][j] = 0;
	 
	    else if (X[i-1] == Y[j-1])
	        L[i][j] = L[i-1][j-1] + 1;
	 
	    else
	        L[i][j] = max(L[i-1][j], L[i][j-1]);
	    }
	}    
	return L[m][n];
}


struct Graph createEdges(struct Graph g){
	int i,j,lcs,firstlength,secondlength;
	struct Node* newnode;
	for (i=0;i<g.size;i++){
		for(j=i+1;j<g.size;j++){
			firstlength = strlen(g.list[i].scanpath);
			secondlength = strlen(g.list[j].scanpath);
			lcs =  lcscalc(g.list[i].scanpath,g.list[j].scanpath,firstlength,secondlength);
			if(lcs >= 5){
				if(g.list[i].next == NULL){
					g.list[i].next = (struct Node*)malloc(sizeof(struct Node));
					strcpy(g.list[i].next->scanpath,g.list[j].scanpath);
					g.list[i].next->weight = lcs;
					g.list[i].next->next = NULL;
					g.list[i].next->id = g.list[j].id;
					strcpy(g.list[i].next->scanpath,g.list[j].scanpath);
				}
				else{
					newnode = (struct Node*)malloc(sizeof(struct Node));
					strcpy(newnode->scanpath,g.list[j].scanpath);
					newnode->weight = lcs;
					newnode->id = g.list[j].id;
					newnode->next = g.list[i].next;
					g.list[i].next = newnode;		
				}	
			}
		}
	}
	return g;
}


void printGraph(struct Graph g){
	int i,counter = 0,max = 0,min,maxid,minid,flag = 0,lcs,firstlength,secondlength;
	struct Node *iter;
	for(i=0;i<g.size;i++){
		printf("%d",g.list[i].id);
		if(g.list[i].next != NULL){
			iter = g.list[i].next;
			while(iter != NULL){
				counter++;
				firstlength = strlen(g.list[i].scanpath);
				secondlength = strlen(iter->scanpath);
				lcs = lcs =  lcscalc(g.list[i].scanpath,iter->scanpath,firstlength,secondlength);
				printf(" -> %d | %d",iter->id,lcs);
				iter = iter->next;
			}
		}
		if(flag == 0){
			min = counter;
			flag = 1;
		}
		if(counter >= max){
			max = counter;
			maxid = g.list[i].id;
		}
		if(counter <= min){
			min = counter;
			minid = g.list[i].id;
		}
		counter = 0;
		printf("\n");
	}
	printf("\nVertex with maximum number of neighbors: %d has %d neighbors\n",maxid,max);
	printf("Vertex with minimum number of neighbors: %d has %d neighbors",minid,min);
}



