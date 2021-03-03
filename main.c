#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "solver.h"
#include "generator.h"
#include "gridDraw.h"

int main()
{

	FILE *fptr; 
	char filename[100] = "welcomeText.txt", c; 
	int difficulty, seed, choice;

	// Open file 
	fptr = fopen(filename, "r"); 
	if (fptr == NULL) 
	{ 
	printf("Cannot open welcome file \n"); 
	exit(0); 
	} 

	// Read contents from file 
	c = fgetc(fptr); 
	while (c != EOF) 
	{ 
	printf ("%c", c); 
	c = fgetc(fptr); 
	} 

	fclose(fptr); 

	printf("Please enter 1 if the grid is to be inputted or 2 if generated : ");

	scanf("%d", &choice);
	printf("%d\n", choice);
	switch(choice)
	{
		case 2:
		printf("Enter a positive integer seed for generation of the sudoku, and -1 for a random seed.\n");
		scanf("%d", &seed);

		srand(time(0));
		setSeed(seed == -1? rand():seed);


		printf("Please enter a number between 20 -81 the difficulty of the sudoku desired, the larger tha numbers, less the number of blanks. Recommended difficulty - 45 : ");
		scanf("%d", &difficulty);

		generateGrid(difficulty);
		printf("Randomly Generated Grid - \n");
		drawGrid();break;
		
		
		case 1:
		printf("Enter the grid with -1 for spaces and a newline after every 9 entries : \n");
		inputGrid();
	        drawGrid();	break;

		default:

		printf("Incorrect Option.");
	}
	
	if(choice == 1 || choice == 2)
	{
		printf("The solved sudoku puzzle - \n");
		solve();
	}

	return 1;

}
