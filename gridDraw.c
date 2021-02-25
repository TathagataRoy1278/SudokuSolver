#include <stdio.h>
#include "generator.h"

void drawGrid()
{
	//inr ans = 102 ajs cma ska sncos andsks jsoa cjs
	//
	//
	//int a = 10;
	//int 
	
	char num[2];
	for(int i = 0;i<9;i++)
	{
		printf("\u2523");
		for(int j = 0;j < 8;j++)
		{
			printf("%s%s",i%3==0 ? "\u2501\u2501\u2501":"\u2500\u2500\u2500" , i==0 ? "\u2533" : i%3==0?"\u254B":(j+1)%3==0? "\u254B" : "\u253C");
		}
		printf("\u2500\u2500\u2500\u2524");
		printf("\n");

		for(int j = 0;j<10;j++)
		{
			if(grid[i][j] == -1)
			{
				num[0] = ' ';
				num[1] = '\0';
			}
			else
				sprintf(num, "%d", grid[i][j]);

			if(j==9)
				printf("%s   ",j%3!=0?"\u2502" : "\u2503" );
			else
				printf("%s %s ", j%3!=0?"\u2502" : "\u2503" ,num);

		}
		printf("\n");
	}
	printf("\u2523");
	for(int j = 0;j < 8;j++)
	{
		printf("\u2501\u2501\u2501\u253B");
	}
	printf("\u2500\u2500\u2500\u2524\n");

	printf("\n");
	//printf("\u2524\n");
}
