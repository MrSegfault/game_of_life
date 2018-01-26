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
	
	while(1){ //proceed forever
		t++;
		for(i=0;i<rows;i++){ //for every item in the matrix
			for(j=0;j<cols;j++){
				count=0;
				lim1=(j>0)?-1:0; //check if we can expect neighbors from left and right
				lim2=(j<cols-1)?1:0;
				if(i>0){ //if there are neighbors over one item
					for(n=lim1;n<=lim2;n++){
						if(matrix[i-1][j+n]==ALIVE){count++;}
					}
				}
				if(j>0 && matrix[i][j-1]==ALIVE){count++;} //same line as the item, left and right
				if(j<cols-1 && matrix[i][j+1]==ALIVE){count++;}
				if(i<rows-1){ //neighbors under the item
					for(n=lim1;n<=lim2;n++){
						if(matrix[i+1][j+n]==ALIVE){count++;}
					}
				}
				if(matrix[i][j]==ALIVE){ //check if the cell is bound to die or be born
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
			memcpy(&matrix[i],&next[i],cols); //store the "next matrix" as the current matrix
			memcpy(&printer[i*cols+i],&matrix[i],cols); //update the printer
		}
		puts("\n\n");
		PRINT_IT; //print iteration
		usleep(100000); //wait for a while
	}
}

