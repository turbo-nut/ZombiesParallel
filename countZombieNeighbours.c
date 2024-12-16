#include "vars_defs_functions.h"

int countZombieNeighbours(int row, int col, CELL **current) {
	int rowPrev, rowNext;
	int colPrev, colNext;
	int counter = 0;

	rowPrev = row-1;
	rowNext = row+1;

	colPrev = col-1;
	colNext = col+1;

	//wrap values to first/last index
	if (row == 0)
	{
		rowPrev = ROWS-1;
	}
	if (row == ROWS-1)
	{
		rowNext = 0;
	}


	if (col == 0)
	{
		colPrev = COLS-1;
	}
	if (col == COLS-1)
	{
		colNext = 0;
	}

	//#if DEBUG_LEVEL >1 
	//printf("rowPrev: %d\t rowNext: %d\n",rowPrev,rowNext);
	//printf("colPrev: %d\t colNext: %d\n", colPrev, colNext);
	//#endif

	//check if neighboring cells are Zombies
	if (current[rowPrev][colPrev].state == 'Z')
	{
		counter++;
	}

	if (current[rowPrev][col].state == 'Z')
	{
		counter++;
	}
	
	if (current[rowPrev][colNext].state == 'Z')
	{
		counter++;
	}
	
	if (current[row][colPrev].state == 'Z')
	{
		counter++;
	}
	
	if (current[row][colNext].state == 'Z')
	{
		counter++;
	}

	if (current[rowNext][colPrev].state == 'Z')
	{
		counter++;
	}

	if (current[rowNext][col].state == 'Z')
	{
		counter++;
	}

	if (current[rowNext][colNext].state == 'Z')
	{
		counter++;
	}
return counter;
}
