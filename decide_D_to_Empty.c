#include <stdio.h>
#include "vars_defs_functions.h"

void decide_D_to_Empty(int row,
int col,
long *ptr_to_numD,
CELL **current,
CELL **future){
	//use the counter d to empty variable
	//once it reaches 0 - make it empty

	if (current[row][col].counter_D_to_Empty == 0) 
	{
		future[row][col].state = ' ';

		current[row][col].stateChange = 'Y';

		(*ptr_to_numD)--;
	
		#if DEBUG_LEVEL > 1
		printf("Cell [%d][%d]: EMPTY\n", row,col);
		#endif
	}

	else
	{
		//decrement counter
		(current[row][col].counter_D_to_Empty)--;
	
	}
}


