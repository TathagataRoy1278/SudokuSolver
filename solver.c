#include <stdio.h>
#include <math.h>
#include "generator.h"
#include <string.h>
#include "gridDraw.h"
#include <stdlib.h>
#include <time.h>


#define true 1
#define false 0

int possibilities[9][9][9];
int singleCandidates[81];

//constants
const int arrayneg1[9] = {-1,-1,-1,-1,-1,-1,-1,-1,-1};
const int array1[9] = {1,1,1,1,1,1,1,1,1};
const int array0[9] =  {0};

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

		//
		//
		//0 1 2 3 4 5 6 7 8
		//0 1 1 1 0 1 1 1 0 
		//
		//

		for(j = 0;j<9;j++)
			if(grid[i][j] == -1)
				if(memcmp(possibilities[i][j],array0,sizeof(possibilities[i][j])) == 0)
					memcpy(possibilities[i][j],rowPossibilities, sizeof(possibilities[i][j]));
				else
					arrayAND(i,j,&possibilities[i][j][0], &rowPossibilities[0]);//remove anding to increase efficiency
			else	
				memcpy(possibilities[i][j], arrayneg1, sizeof(possibilities[i][j]));

		//for cols
		//
		//stores all the possible values taking into account  coloumns
		//then it merged both by using AND on the two arrays
		//obtained by checking row and coloumn possibilities

		

	}

	for(int j = 0;j<9;j++)
	{
		int colPossibilities[9] = {1,1,1,1,1,1,1,1,1};

		for(int i = 0;i<9;i++)
			if(!(grid[i][j] == -1))
				colPossibilities[grid[i][j]-1] = 0;
		for(int i = 0;i<9;i++)
		{
			if(grid[i][j]==-1)
				arrayAND(i,j,&possibilities[i][j][0], &colPossibilities[0]);
			else 
				memcpy(possibilities[i][j], arrayneg1, sizeof(possibilities[i][j]));
		}
	}


	//1 0 0 1 1 0 0 1 1 - rows
	//1 1 1 0 1 1 0 0 0 - coloumn
	//
	//1 0 0 0 1 0 0 0 0







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

}

int printPossibilities()
{
	for(int i = 0;i<9;i++)
	{
		for(int j = 0;j<9;j++)
		{
			printf("(%d, %d) [", i, j);
			for(int k = 0;k<9;k++)
				printf("%d, ", possibilities[i][j][k]);
			printf("], \n");
		}
		printf("\n");
	}
}

void setBoxPossibilities()
{
	int boxPossibilities[9];


	for(int i = 0;i<3;i++)
	{
		memcpy(boxPossibilities, array1, sizeof(boxPossibilities));
		for(int j = 0;j<3;j++)
		{
			memcpy(boxPossibilities, array1, sizeof(boxPossibilities));
			for(int row = i*3;row<(i+1)*3;row++)
				for(int col = j*3; col<(j+1)*3;col++)
					if(grid[row][col]!=-1)
						boxPossibilities[grid[row][col]-1] = 0;

			for(int row = i*3;row<(i+1)*3;row++)
                                for(int col = j*3; col<(j+1)*3;col++)
					if(grid[row][col] == -1)
                                        	arrayAND(row,col,&possibilities[row][col][0],&boxPossibilities[0]);

		} 
		

	}
}

int numberOfSingleCandidates()
{	
	//can be optimized using a linked list

	int numberOfCandidates = 0;
	int ctr = 0;
	for(int i = 0;i<9;i++)
		for(int j = 0;j<9;j++)
		{
			numberOfCandidates = 0;
			for(int k = 0;k < 9;k++)
			{
				if(possibilities[i][j][k]!=-1)
					numberOfCandidates += possibilities[i][j][k];
				else 
					break;
			}
			if(numberOfCandidates==1)
				singleCandidates[ctr++] = i*9+j+1;
		}
	
	

	if(ctr)
		return 1;
	else
		return 0;
}

int fillSingleCandidates()
{
	for(int i = 0;i<81;i++)
	{
		if(singleCandidates[i] == 0)
			break;
		
		int row = (singleCandidates[i]-1)/9;
		int col = (singleCandidates[i]-1)%9;

		int candidate = -1;
		for(candidate = 0;candidate<9;candidate++)
		{
			if(possibilities[row][col][candidate]==1)
				break;
		}
		if(candidate<9 && candidate>=0)
		{
			grid[row][col] = candidate+1;
			memcpy(possibilities[row][col],arrayneg1, sizeof(possibilities[row][col]));
		}
	

	}
	int tmpArr[81] = {0};
	memcpy(singleCandidates, tmpArr, sizeof(singleCandidates));

}

int gridSolved()
{
	
	for(int i = 0;i<9;i++)
		for(int j = 0;j<9;j++)
			if(grid[i][j] == -1)
				return 0;

	return 1;
}

int gridValid(int i, int j, int target)
{
	if(!existsInRow(i,target) && !existsInCol(j,target) && !existsInBox(i,j, target))
		return 1;
	else 
		return 0;

}


int find_empty_cell( int *row, int *column) {
  for (int x = 0; x < 9; x++) {
    for (int y = 0; y < 9; y++) {
      if (grid[x][y]==-1) {
        *row = x;
        *column = y;

        return 1;
      }
    }
  }
  return 0;
}

int solve_sudoku()
{
    int row;
    int col;
    if(find_empty_cell(&row, &col) == 0)
        return 1;
    int i;
    for(i=0;i<9;i++)
    {
	if(possibilities[row][col][i]==-1)
		break;

	if(possibilities[row][col][i]==1)
        if(gridValid( row, col,i+1))
        {
            grid[row][col] = i+1;
            //backtracking
            if(solve_sudoku())
                return 1;
            
            grid[row][col]=-1;
        }
    }
    return 0;
}


int init()
{
	for(int i =0;i<9;i++)
		for(int j = 0;j<9;j++)
			memcpy(possibilities[i][j], array0, sizeof(possibilities[i][j]));

	for(int i =0;i<81;i++)
		singleCandidates[i] = 0;
}

int solve()
{
	//inputGrid();
	//generateGrid(20);
	//drawGrid();

	init();

	printf("\n");
	setBasicPossibilities(); 
	setBoxPossibilities();

	//fillSingleCandidates();
	while(numberOfSingleCandidates()!=0)
	{
		fillSingleCandidates();
		
		//drawGrid();

         	printf("\n");
        	setBasicPossibilities();
	        setBoxPossibilities();

		//printGrid();
	}



	if(!gridSolved())
	{
		solve_sudoku();
	}
	
	if(!gridSolved())
		printf("This grid has no Solution.\n");
	else
		drawGrid();
}
