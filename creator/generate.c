#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int na[9];

int *shiftArray(int shiftValue)
{

	int a[9] = {1,2,3,4,5,6,7,8,9};
	
	for(int i = 0;i<9;i++)
	{
		na[(i+shiftValue)%9] = a[i];
	}
	
	printf("Printing array.\n");

	for(int i = 0 ;i<9;i++)
	{
		printf("%d, ",na[i]);
	}

	printf("\n");


	return &na[0];
}

int main()
{
	int  grid[9][9];
	int difficulty = 21;


	srand(time(0));
	unsigned long seed = rand();
	//printf("%lu\n", seed);
	while(seed<9)
	{
		seed = seed*seed;
	}

	seed = seed%1000000000;

	for(int i = 0;i<9;i++)
	{
		int tmp[9];
	
		int *na_p;
		if(i!=0)
			na_p = shiftArray((seed%(int)pow(10,i+1))/(int)pow(10,i));
		else
			na_p = shiftArray(seed%10);
		
		//srand(time(0));

		for(int j = 0;j<9;j++)
		{
			
			if(rand()%100 < ((float)difficulty/81.0*100))	
					tmp[j] = -1;
			else
				tmp[j] = *(na_p+j);
		}
		
		for(int j = 0;j<9;j++)
			grid[i][j] = tmp[j];
		//grid[i] = 
	}


	for(int i = 0;i<9;i++)
	{
		for(int j = 0;j<9;j++)
			if(grid[i][j] == -1)
				printf("_ ");
			else
				printf("%d ", grid[i][j]);
		printf("\n");
	}
}




//1 2 3 4 5 6 7 8 9
//9 1 2 3 4 5 6 7 8
//8 9 1 2 3 4 5 6 7
//7 8 9 1 2 3 4 5 6
//6 7 8 9 1 2 3 4 5
//5 6 7 8 9 1 2 3 4
//4 5 6 7 8 9 1 2 3
//3 4 5 6 7 8 9 1 2
//2 3 4 5 6 7 8 9 1
