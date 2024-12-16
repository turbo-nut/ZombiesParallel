#include "vars_defs_functions.h"
#include <stdlib.h>
void decide_Z_to_D(int row, int col, int num_Susceptible_Neighbours,
                   long *ptr_to_numZ, long *ptr_to_numD, CELL **current,
                   CELL **future) {
  // if less than 6, run the check
  // basically just like S -> Z or R file
  double killChance = PROB_S_TO_Z_1 * (num_Susceptible_Neighbours +
                                       (num_Susceptible_Neighbours * 0.5));
  double savingThrow = (rand() % (100 + 1 - 1) + 1) * 0.01;

  if (num_Susceptible_Neighbours == NUM_S_TO_DEFEAT_Z) {
    int newThrow = savingThrow * 10;
    future[row][col].state = 'D';
#if DEBUG_LEVEL > 1
    printf("Zombie [%d][%d]: DEFEATED\n", row, col);
#endif
    (*ptr_to_numD)++;
    (*ptr_to_numZ)--;
    current[row][col].stateChange = 'Y';
  }

  else if (killChance > savingThrow) {
    future[row][col].state = 'D';
    (*ptr_to_numD)++;
    (*ptr_to_numZ)--;
    current[row][col].stateChange = 'Y';
  }

  else {
    future[row][col].state = 'Z';
  }
}
