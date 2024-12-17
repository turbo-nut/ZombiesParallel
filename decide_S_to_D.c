#include <stdio.h>
#include <stdlib.h>
#include "vars_defs_functions.h"

void decide_S_to_D(int row,
		   int col,
		   int num_Zombie_Neighbours,
		   long *ptr_to_numS,
		   long *ptr_to_numD,
		   CELL **current,
		   CELL **future){
	float deathChance = (float)rand() / (double)RAND_MAX;
    if (deathChance > 0.99) {
      future[row][col].state = 'D';
      (*ptr_to_numD)++;
      (*ptr_to_numS)--;
      current[row][col].stateChange = 'Y';
#if DEBUG_LEVEL > 1
      printf("Cell [%d],[%d]: DEATH TO NATURAL CAUSES \n", row, col);
#endif
    } else {
      future[row][col].state = 'S';
      current[row][col].stateChange = 'N';
    }

}
