#include<stdio.h>
#include<stdlib.h>
#include<string.h>


struct Student{
	int isempty; /*1->occupied 0->empty*/
	char id[3];
	char name[40];
	char dept[3];
};


void AddStudent(struct Student* hashtable,int size,int choice){
	char id[3],name[40],dept[3];
	printf("Enter unique identifier: ");
	scanf("%s",id);
	printf("Enter name: ");
	scanf("%s",dept);
	printf("Enter department: ");
	scanf("%s",dept);
}


void print(struct Student* hashtable,int size){
	int i;
	for(i=0;i<size;i++){
		if(hashtable[i].isempty == 1){
			printf("Id: %s\n",hashtable[i].id);
			printf("name: %s\n",hashtable[i].name);
			printf("dept: %s\n\n",hashtable[i].dept);
		}
	}
}

int main(){
	
	struct Student hashtable[11];
	int loadfactor,addressingchoice,funcchoice;
	
	printf("(1)Double hashing\n(2)Quadratic probing\nEnter your choice: ");
	scanf("%d",&addressingchoice);
	
	while(1){
		printf("(1)Add a student\n");
		printf("(2)Search a student\n");
		printf("(3)Print table\n");
		printf("(4)Exit\n");
		printf("Enter the command: ");
		scanf("%d",&funcchoice);
		if(funcchoice == 1){
			
		}
		else if(funcchoice == 2){
			print(hashtable,11);
		}
		else if(funcchoice == 3){
			printf("Enter a valid command!\n");
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
