#include "vars_defs_functions.h"
#include <stdio.h>

void decide_R_to_Z(int row, int col, long *ptr_to_numR, long *ptr_to_numZ,
                   CELL **current, CELL **future) {

  // keep track of the counter, and when it's done, set the
  // state from 'R' to Z
  if (current[row][col].counter_R_to_Z == 0) {
    future[row][col].state = 'Z';
    current[row][col].stateChange = 'Y';

#if DEBUG_LEVEL > 1
    printf("Zombie at [%d][%d]: RESURRECTED\n", row, col);
#endif

    // make sure pointers are updated
    (*ptr_to_numZ)++;
    (*ptr_to_numR)--;

  }

  // now i need to decrement the counter if it's not empty
  // to do this i can just (counter to Z)--
  //
  else {
    (current[row][col].counter_R_to_Z)--;
  }
}
