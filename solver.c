#include <stdio.h>
#include <math.h>
#include "generator.h"
#include <string.h>

#define true 1
#define false 0

int possibilities[9][9][9];

//constants
const short arrayneg1[9] = {-1,-1,-1,-1,-1,-1,-1,-1,-1};


int existsInRow(int i, int target)
{
	for(int col = 0;col<9;col++)
		if(grid[i][col] == target)
			return true;

	return false;
}

int existsInCol(int i, int target)
{
	for(int row = 0;row<9;row++)
		if(grid[row][i] == target)
			return true;

	return false;
}

int existsInBox(int i, int j, int target)
{
	short boxCol = floor(j/3.0);
	short boxRow = floor(i/3.0);
	
	//1 2 3
	//4 5 6
	//7 8 9
	
	for(int row = boxRow*3;row<(boxRow+1)*3;row++)
		for(int col = boxCol*3;col<(boxCol+1)*3;col++)
			if(grid[row][col] == target)
				return true;

	return false;
}


int arrayAND(int i, int j,int *a1, int *a2)
{

	int *tmpAdd = a1;
	int nA[9];//'anded' array


	for(int k = 0;k<9;k++)
	{
		possibilities[i][j][k] = *(tmpAdd) * *(a2++);
		tmpAdd++;
	}

	return 1;
}


int setBasicPossibilities()//checks Row and Coloumns entries
{
	int i,j;
	for(i = 0;i<9;i++)
	{

		//for rows
		//
		//stores all the possible values at i,j taking into account only rows
		//
		int rowPossibilities[9] = {1,1,1,1,1,1,1,1,1};

		for(j = 0;j<9;j++)
			if(!(grid[i][j] == -1))
				rowPossibilities[grid[i][j]-1] = 0;
		for(j = 0;j<9;j++)
			if(grid[i][j] == -1)
				memcpy(possibilities[i][j],rowPossibilities, sizeof(possibilities[i][j]));
			else	
				memcpy(possibilities[i][j], arrayneg1, sizeof(possibilities[i][j]));

		//for cols
		//
		//stores all the possible values taking into account  coloumns
		//then it merged both by using AND on the two arrays
		//obtained by checking row and coloumn possibilities

		int colPossibilities[9] = {1,1,1,1,1,1,1,1,1};

		for(j = 0;j<9;j++)
		{
			if(!(grid[j][i] == -1))
				colPossibilities[grid[j][i]-1] = 0;
		}
		
		for(j = 0;j<9;j++)
		{
			if(grid[j][i]==-1)
				arrayAND(j,i,&possibilities[j][i][0], &colPossibilities[0]);
			else
				memcpy(possibilities[j][i], arrayneg1, sizeof(possibilities[j][i]));
			
		}

	}
/*
	for(int j = 0;j<9;j++)
	{
		int colPossibilities[9] = {1,1,1,1,1,1,1,1,1};

		for(int i = 0;i<9;i++)
			if(!(grid[i][j] == -1))
				colPossibilities[grid[i][j]-1] = 0;
		for(int i = 0;i<9;i++)
		{
			if(grid[i][j]
			arrayAND(i,j,&possibilities[i][j][0], &colPossibilities[0]);
		}
	}*/
}

void printGrid()
{
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
        printf("%d\n", existsInBox(3,1,6));

}

int printPossibilities()
{
	for(int i = 0;i<9;i++)
	{
		for(int j = 0;j<9;j++)
		{
			printf("[");
			for(int k = 0;k<9;k++)
				printf("%d, ", possibilities[i][j][k]);
			printf("], ");
		}
		printf("\n");
	}
}

int main()
{
	setSeed(789876);
	inputGrid();
	
	printGrid();
	printf("\n");

	setBasicPossibilities();
	printPossibilities();
}
