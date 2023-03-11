/*
CNG 315 Assignment 1
Oguzhan Alpertürk
2315752

Note: References for heap operations:
 "https://www.geeksforgeeks.org/heap-sort-for-decreasing-order-using-min-heap/"
  https://www.geeksforgeeks.org/building-heap-from-array/	

*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Champion{
	char name[20];
	float expectedWinRate; 
	int NumberOfWins;  
	int NumberOfBattles;  
	float ActualWinRate;
	float ExpectationSkew;
};

struct Champs{
	struct Champion* champ;
	int size;
};

struct clinearguments{
	int sortingCriteria;
	char ChampionDataFile[20];
	char BattlesDataFile[20];
};

struct Champs initializeChampions(char filename[25]);

void printLeaderboard(struct Champs c);

struct Champs getBattleData(struct Champs c,char filename[20]);

struct Champs computeWinRate(struct Champs c);

struct Champs swap(struct Champs c,int i1,int i2);

struct Champs heapify(struct Champs c, int n, int i,int criteria);

struct Champs buildHeap(struct Champs c, int n,int criteria);

struct Champs heapSort(struct Champs c, int n,int criteria);

struct clinearguments parseInput(int argc,char *argv[]);




int main(int argc,char *argv[]){
	
	
	
	struct Champs c;
	struct clinearguments args;
	args = parseInput(argc, argv);
	c = initializeChampions(args.ChampionDataFile);
	c = getBattleData(c,args.BattlesDataFile);
	c = computeWinRate(c);
	c = heapSort(c,c.size,args.sortingCriteria);
	printLeaderboard(c);

	
	
	return 0;
}



struct clinearguments parseInput(int argc,char *argv[]){
	int i,a;
	struct clinearguments ret;
	
	if(argc == 1){
		printf("Please provide command line argumands\n ");

	}
	for(i=1;i<=argc;i++){
		
		if(i==1){
			a = atoi(argv[i]);
			ret.sortingCriteria = a;
		}
		else if(i==2){
			strcpy(ret.ChampionDataFile,argv[2]);
		}
		else if(i==3){
			strcpy(ret.BattlesDataFile,argv[3]);
		}
	}
	
	return ret;
}

struct Champs initializeChampions(char filename[25]){
	
	struct Champs c;
	c.champ = (struct Champion*)malloc(sizeof(struct Champion));
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
			c.champ = (struct Champion*)realloc(c.champ,sizeof(struct Champion)*c.size);	
			elementno++;
			strcpy(line,strtok(str," "));
			strcpy(c.champ[elementno].name,line);
			i=0;
			while(1){
				if(i==0){
					piece = strtok(NULL, " ");
					c.champ[elementno].expectedWinRate = atof(piece);
					c.champ[elementno].NumberOfBattles = 0;
					c.champ[elementno].NumberOfWins = 0;
					c.champ[elementno].ActualWinRate = 0;
					c.champ[elementno].ExpectationSkew = 0;
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

struct Champs getBattleData(struct Champs c,char filename[20]){
	FILE *ffile;
	char str[100];
	char line[100];
	char *piece;
	ffile = fopen(filename,"r");
	int i,j;
 
	while(1){
		if(fgets(str,sizeof(str),ffile) == NULL){
			break;
		}
		else{	
			strcpy(line,strtok(str," "));
			i=0;
			while(1){
				if(i==0){
					piece = strtok(NULL, " ");
					for(j=0;j<c.size;j++){
						if(strcmp(c.champ[j].name,piece) == 0){
							c.champ[j].NumberOfBattles++;
						}
					}
						if(piece == NULL){
							break;
					}	}
					else if(i==1){
					piece = strtok(NULL, " ");
					for(j=0;j<c.size;j++){
						if(strcmp(c.champ[j].name,piece) == 0){
							c.champ[j].NumberOfBattles++;
						}
					}
						if(piece == NULL){
							break;
					}	}
					else if(i==2){
					piece = strtok(NULL, "\n");
					for(j=0;j<c.size;j++){
						if(strcmp(c.champ[j].name,piece) == 0){
							c.champ[j].NumberOfWins++;
						}
					}
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

void printLeaderboard(struct Champs c){
	int i,j,space;
	
	printf("Champion    ");
	printf("Battles       ");
	printf("Win        ");
	printf("AWR           ");
	printf("EWR           ");
	printf("Skew\n");
	
	for(i=0;i<c.size;i++){
		printf("%s",c.champ[i].name);
		space = 12 - strlen(c.champ[i].name);
		for(j=0;j<space;j++){
			printf(" ");
		}
		printf("%d             ",c.champ[i].NumberOfBattles);
		printf("%d          ",c.champ[i].NumberOfWins);
		printf("%.2f          ",c.champ[i].ActualWinRate);
		printf("%.2f          ",c.champ[i].expectedWinRate);
		printf("%.2f\n",c.champ[i].ExpectationSkew);
	}
}

struct Champs computeWinRate(struct Champs c){
	int i;
	float winRateRatio;
	for(i=0;i<c.size;i++){
		
		c.champ[i].ActualWinRate = (float)(c.champ[i].NumberOfWins) / (c.champ[i].NumberOfBattles);
		winRateRatio = (c.champ[i].ActualWinRate) / (c.champ[i].expectedWinRate);
		c.champ[i].ExpectationSkew = winRateRatio -1;
		if(c.champ[i].ExpectationSkew < 0){
			c.champ[i].ExpectationSkew = c.champ[i].ExpectationSkew * -1;
		} 
	}
	return c;
}

struct Champs swap(struct Champs c,int i1,int i2){
	struct Champion temp;
	temp.ActualWinRate = c.champ[i1].ActualWinRate;
	temp.ExpectationSkew = c.champ[i1].ExpectationSkew;
	temp.expectedWinRate = c.champ[i1].expectedWinRate;
	strcpy(temp.name,c.champ[i1].name);
	temp.NumberOfBattles = c.champ[i1].NumberOfBattles;
	temp.NumberOfWins = c.champ[i1].NumberOfWins;
	
	c.champ[i1].ActualWinRate = c.champ[i2].ActualWinRate;
	c.champ[i1].ExpectationSkew = c.champ[i2].ExpectationSkew;
	c.champ[i1].expectedWinRate = c.champ[i2].expectedWinRate;
	strcpy(c.champ[i1].name,c.champ[i2].name);
	c.champ[i1].NumberOfBattles = c.champ[i2].NumberOfBattles;
	c.champ[i1].NumberOfWins = c.champ[i2].NumberOfWins;
	
	c.champ[i2].ActualWinRate = temp.ActualWinRate;
	c.champ[i2].ExpectationSkew = temp.ExpectationSkew;
	c.champ[i2].expectedWinRate = temp.expectedWinRate;
	strcpy(c.champ[i2].name,temp.name);
	c.champ[i2].NumberOfBattles = temp.NumberOfBattles;
	c.champ[i2].NumberOfWins = temp.NumberOfWins;
	
	return c;
}

struct Champs heapify(struct Champs c, int n, int i,int criteria){
    int smallest = i; // Initialize largest as root
    int l = 2 * i + 1; // left = 2*i + 1
    int r = 2 * i + 2; // right = 2*i + 2
    int temp;
 	
 	if(criteria == 1){
 		// If left child is larger than root
	    if (l < n && c.champ[l].ActualWinRate < c.champ[smallest].ActualWinRate)
	        smallest = l;
	 
	    // If right child is larger than largest so far
	    if (r < n && c.champ[r].ActualWinRate < c.champ[smallest].ActualWinRate)
	        smallest = r;
	 
	    // If largest is not root
	    if (smallest != i) {
	        c = swap(c,i,smallest);
	 
	        // Recursively heapify the affected sub-tree
	        heapify(c, n, smallest,criteria);
	    }
	 } 
	 else if(criteria == 2){
	 	// If left child is larger than root
	    if (l < n && c.champ[l].expectedWinRate < c.champ[smallest].expectedWinRate)
	        smallest = l;
	 
	    // If right child is larger than largest so far
	    if (r < n && c.champ[r].expectedWinRate < c.champ[smallest].expectedWinRate)
	        smallest = r;
	 
	    // If largest is not root
	    if (smallest != i) {
	        c = swap(c,i,smallest);
	 
	        // Recursively heapify the affected sub-tree
	        heapify(c, n, smallest,criteria);
	    }
	 }
	 else if(criteria == 3){
	 	// If left child is larger than root
	    if (l < n && c.champ[l].ExpectationSkew < c.champ[smallest].ExpectationSkew)
	        smallest = l;
	 
	    // If right child is larger than largest so far
	    if (r < n && c.champ[r].ExpectationSkew < c.champ[smallest].ExpectationSkew)
	        smallest = r;
	 
	    // If largest is not root
	    if (smallest != i) {
	        c = swap(c,i,smallest);
	 
	        // Recursively heapify the affected sub-tree
	        heapify(c, n, smallest,criteria);
	    }
	 }
    
    return c;
}

struct Champs buildHeap(struct Champs c, int n,int criteria){
    // Index of last non-leaf node
    int i;
    int startIdx = (n / 2) - 1;
 
    // Perform reverse level order traversal
    // from last non-leaf node and heapify
    // each node
	if(criteria == 1){
		for (i = startIdx; i >= 0; i--) {
        c = heapify(c, n, i,criteria);
   		}
	}
	else if(criteria == 2){
		for (i = startIdx; i >= 0; i--) {
        c = heapify(c, n, i,criteria);
    	}
	}
	else if(criteria==3){
		for (i = startIdx; i >= 0; i--) {
        c = heapify(c, n, i,criteria);
    	}
	}
	return c;
}

struct Champs heapSort(struct Champs c, int n,int criteria){
	
	c = buildHeap(c,c.size,criteria);
	
	int i,temp;
    // Build heap (rearrange array)
    if(criteria == 1){
    	for (i = n / 2 - 1; i >= 0; i--)
	        c = heapify(c, n, i,criteria);
	 
	    // One by one extract an element from heap
	    for (i = n - 1; i >= 0; i--) {
	    	c = swap(c,0,i);
	        // Move current root to end
	        // call max heapify on the reduced heap
	        c = heapify(c, i, 0,criteria);
   		}
	}
	else if(criteria == 2){
		for (i = n / 2 - 1; i >= 0; i--)
	        c = heapify(c, n, i,criteria);
	 
	    // One by one extract an element from heap
	    for (i = n - 1; i >= 0; i--) {
	    	c = swap(c,0,i);
	        // Move current root to end
	        // call max heapify on the reduced heap
	        c = heapify(c, i, 0,criteria);
	    }
	}
	else if(criteria == 3){
		for (i = n / 2 - 1; i >= 0; i--)
	        c = heapify(c, n, i,criteria);
	 
	    // One by one extract an element from heap
	    for (i = n - 1; i >= 0; i--) {
	    	c = swap(c,0,i);
	        // Move current root to end
	        // call max heapify on the reduced heap
	        c = heapify(c, i, 0,criteria);
	    }
	}
    
    return c;
}

