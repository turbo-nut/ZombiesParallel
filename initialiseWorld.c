#include "vars_defs_functions.h"
#include <stdio.h>
#include <stdlib.h>
void initialiseWorld(CELL **current, CELL **future, long *ptr_to_numS,
                     long *ptr_to_numZ) {

  printf("Initialising World...\n");

  unsigned int i, j, randRow, randCol;

  for (i = 0; i < ROWS; i++) {
    for (j = 0; j < COLS; j++) {
      current[i][j].state = 'S';
      current[i][j].stateChange = 'N';
      (*ptr_to_numS)++;

      // need to code a time to resurrect the removed
      // use max and min numbers from the vars defs funcs
      current[i][j].counter_I_to_Z =
          rand() % (MAX_TIME_I_TO_Z - MIN_TIME_I_TO_Z + 1) + MIN_TIME_I_TO_Z;
      current[i][j].counter_R_to_Z =
          rand() % (MAX_TIME_R_TO_Z - MIN_TIME_R_TO_Z + 1) + MIN_TIME_R_TO_Z;

      // cell needs to be empty after something dies so that a new S or Z can be
      // "Birthed"
      current[i][j].counter_D_to_Empty = TIME_D_TO_EMPTY;

      // copy everything so that they're identical at first, once the day loop
      // runs for the first time it'll all be different
      future[i][j] = current[i][j];
    }
  }

  // infecting patient zero
  // grabs a random row and column that'll be used for setting
  // a random cell state to 'Z'
  for (int k = 0; k <= 50; k++) {
    randRow = rand() % ROWS;
    randCol = rand() % COLS;
    // patient zero placed into world
    current[randRow][randCol].state = 'Z';
    (*ptr_to_numS)--;
    (*ptr_to_numZ)++;
  }
}
