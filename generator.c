#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "generator.h"
#include <string.h>

int na[9];
int grid[9][9];
unsigned long seed = 90;
int box[9] = {1,2,3,4,5,6,7,8,9};

int arrayzero[9] = {0};
int entries[9];


short seed_given = 0;


void setSeed(long n)
{
	seed = n;
	while(seed<=999999999)
		seed*=seed;

	seed%=999999999;
	seed_given = 1;
}

void setRandomSeef()
{
	srand(time(0));
	seed = rand();

}

int *shiftArray(int shiftValue)
{

	int a[9] = {1,2,3,4,5,6,7,8,9};
	
	for(int i = 0;i<9;i++)
	{
		na[(i+shiftValue)%9] = a[i];
	}	

	return &na[0];
}

int fillGridValues()
{
	int difficulty = -1;


	srand(time(0));
	
	seed = seed/1000000000.0;

	

}

int fact(int n)
{
	int product = 1;
	for(int i = 1;i<n;i++)
		product*=i;

	return product;
}

int getGrid(long tmpSeed)
{


	for (int i = 9-1; i >= 0; --i)
	{
   		
		int j = tmpSeed % (i+1);
		tmpSeed/=(i+1);

	   	int temp = box[i];
   		box[i] = box[j];
	     	box[j] = temp;
	}	

}

void inputGrid()
{
	short nOI = 0;//numberOfInputs

	while(nOI<81)
	{
		scanf("%d", &grid[nOI/9][nOI%9]);
		nOI++;
	}	
}

int generateGrid()
{
	int ctr;

	srand(time(0));
	for(int i = 0;i<3;i++)
	{
		memcpy(entries, arrayzero, sizeof(entries));
		ctr = 0;
		getGrid(seed*(i+1));
		for(int j = i*3;j<(i+1)*3;j++)
			for(int k = i*3;k<(i+1)*3;k++)
			{
				grid[j][k] = box[ctr++];
			}

	}


}
/*
int main()
{
	generateGrid();
	for(int i = 0;i<9;i++)
        {
                for(int j = 0;j<9;j++)
                {
                        if(grid[i][j] == -1)
                                printf("_ ");
                        else
                                printf("%d ", grid[i][j]);

                        if((j+1)%3==0)
                                printf("  ");
                }

                printf("\n");

                if((i+1)%3==0)
                        printf("\n");
        }

}*/
/*
 *
1 2 3 4 5 6 7 8 9
9 1 2 3 4 5 6 7 8
8 9 1 2 3 4 5 6 7
7 8 9 1 2 3 4 5 6
6 7 8 9 1 2 3 4 5
5 6 7 8 9 1 2 3 4
4 5 6 7 8 9 1 2 3
3 4 5 6 7 8 9 1 2
2 3 4 5 6 7 8 9 1

*/
