#include <stdio.h>
int main()
{
	//inr ans = 102 ajs cma ska sncos andsks jsoa cjs
	//
	//
	//int a = 10;
	//int 
	

	for(int i = 0;i<9;i++)
	{
		printf("\u251C");
		for(int j = 0;j < 8;j++)
		{
			printf("\u2500\u2500\u2500%s", i == 0 ? "\u252C" : "\u253C");
		}
		printf("\u2500\u2500\u2500\u2524");
		printf("\n");
		for(int j = 0;j<10;j++)
		{
			if(j==9)
				printf("\u2502   ");
			else
				printf("\u2502 %d ", 0);

		}
		printf("\n");
	}
	printf("\u251C");
	for(int j = 0;j < 8;j++)
	{
		printf("\u2500\u2500\u2500\u2534");
	}
	printf("\u2500\u2500\u2500\u2524\n");

	printf("\n");
	//printf("\u2524\n");
}
