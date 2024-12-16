#include "vars_defs_functions.h"

int countSusceptibleNeighbours(int row, int col, CELL **current) {
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
	else if (row == ROWS-1)
	{
		rowNext = 0;
	}


	if (col == 0)
	{
		colPrev = COLS-1;
	}
	else if (col == COLS-1)
	{
		colNext = 0;
	}

	//check if neighboring cells are Susceptible
	if (current[rowPrev][colPrev].state == 'S')
	{
		counter++;
	}

	if (current[rowPrev][col].state == 'S')
	{
		counter++;
	}
	
	if (current[rowPrev][colNext].state == 'S')
	{
		counter++;
	}
	
	if (current[row][colPrev].state == 'S')
	{
		counter++;
	}
	
	if (current[row][colNext].state == 'S')
	{
		counter++;
	}

	if (current[rowNext][colPrev].state == 'S')
	{
		counter++;
	}

	if (current[rowNext][col].state == 'S')
	{
		counter++;
	}

	if (current[rowNext][colNext].state == 'S')
	{
		counter++;
	}





return counter;
}
