#include "vars_defs_functions.h"
#include <stdio.h>
#include <stdlib.h>
void decide_S_to_IorR(int row, int col, int num_Zombie_Neighbours,
                      long *ptr_to_numS, long *ptr_to_numI, long *ptr_to_numR,
                      CELL **current, CELL **future) {
  // if there are zombie neighbours, get the amount of neighbours and use [macro
  // * 0.1+(numZombieNeighbours). if numZN > 6, send em to the soil]
  if (num_Zombie_Neighbours != 0 && num_Zombie_Neighbours < 6) {
    double zombieCheck =
        PROB_S_TO_Z_1 * (num_Zombie_Neighbours + (num_Zombie_Neighbours * 0.5));
    double savingThrow =
        (rand() % (100 + 1 - 1) + 1) * 0.01; //"saving throw" that S will use

    // compare the 2 numbers, if zombieCheck > savingThrow, turn S to Z
    // LATENT MODEL: change Z to I instead and use "decide I to Z" func to
    // determine a Z.
    if (zombieCheck > savingThrow) {
      future[row][col].state = 'I';
      (*ptr_to_numI)++;
      (*ptr_to_numS)--;
      current[row][col].stateChange = 'Y';
#if DEBUG_LEVEL > 1
      printf("Cell [%d],[%d]: INFECTED \n", row, col);
#endif

    } else if (num_Zombie_Neighbours > 6) {
      future[row][col].state = 'R';
      (*ptr_to_numR)++;
      (*ptr_to_numS)--;
      current[row][col].stateChange = 'Y';
#if DEBUG_LEVEL > 1
      printf("Cell [%d],[%d]: REMOVED\n", row, col);
#endif
    } else {
      future[row][col].state = 'S';
      current[row][col].stateChange = 'N';
    }
  }
}
