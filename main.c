#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

#define ERROR_ARG_NO -1
#define ERROR_ARG_VAL -1

#define DEAD ' '
#define ALIVE '#'

#define INIT_PROB 0.5 //probability by which a cell is alive in the first iteration
#define RAND_01 (double)rand()/(double)RAND_MAX //value between 0 and 1
#define PRINT_IT printf("\n%s\n",printer) //print each iteration

typedef char cell; //only one byte for each cell

unsigned int rows;
unsigned int cols;

int main(int argc, char **argv){
	
	unsigned int i,j,count;
	int n,lim1,lim2;
	int t=0;
		
	if(argc != 3){
		printf("Please enter number of rows and columns\n");
		exit(ERROR_ARG_NO);
	}
	
	if(atoi(argv[1]) < 2 || atoi(argv[2]) < 2){
		printf("Please enter values higher than 1\n");
		exit(ERROR_ARG_VAL);
	}
	
	rows = atoi(argv[1]); //store number of rows
	cols = atoi(argv[2]); //store number of columns
	
	cell matrix[rows][cols]; //current matrix
	cell next[rows][cols]; //next matrix
	cell printer[rows*(cols+1)]; //printing the matrix as one big string prevents having too many I/O operations
	for(i=0;i<rows-1;i++){
		printer[i*(cols+1)+cols]='\n'; // add \n at the end of every line
	}
	printer[rows*(cols+1)-1]='\0'; //last char is \0
	
	for(i=0;i<rows;i++){
		for(j=0;j<cols;j++){
			matrix[i][j]=(RAND_01<INIT_PROB)?ALIVE:DEAD; //assign initial values
		}
		memcpy(&printer[i*cols+i],&matrix[i],cols); //copy line by line before printing
		memcpy(&next[i],&matrix[i],cols); //next has to be the same as matrix at the start
	}
	PRINT_IT;
	
	while(1){
		t++;
		for(i=0;i<rows;i++){
			for(j=0;j<cols;j++){
				count=0;
				lim1=(j>0)?-1:0;
				lim2=(j<cols-1)?1:0;
				if(i>0){
					for(n=lim1;n<=lim2;n++){
						if(matrix[i-1][j+n]==ALIVE){count++;}
					}
				}
				if(j>0 && matrix[i][j-1]==ALIVE){count++;}
				if(j<cols-1 && matrix[i][j+1]==ALIVE){count++;}
				if(i<rows-1){
					for(n=lim1;n<=lim2;n++){
						if(matrix[i+1][j+n]==ALIVE){count++;}
					}
				}
				if(matrix[i][j]==ALIVE){
					if(count<2 || count>3){
						next[i][j]=DEAD;
					}
				}else{
					if(count==3){
						next[i][j]=ALIVE;
					}
				}
			}
		}
		for(i=0;i<rows;i++){
			memcpy(&matrix[i],&next[i],cols);
			memcpy(&printer[i*cols+i],&matrix[i],cols);
		}
		puts("\n\n");
		PRINT_IT;
		usleep(100000);
	}
}

