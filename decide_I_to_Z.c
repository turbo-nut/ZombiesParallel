#include "vars_defs_functions.h"
#include <stdio.h>

void decide_I_to_Z(int row, int col, long *ptr_to_numZ, long *ptr_to_numI,
                   CELL **current, CELL **future) {

  if (current[row][col].counter_I_to_Z == 0) {
    future[row][col].state = 'Z';
    current[row][col].stateChange = 'Y';
    (*ptr_to_numZ)++;
    (*ptr_to_numI)--;

#if DEBUG_LEVEL > 1
    printf("Cell [%d][%d]: TURNED\n\n", row, col);
#endif
  }

  else {
    // decrement counter
    (current[row][col].counter_I_to_Z)--;
  }
}
