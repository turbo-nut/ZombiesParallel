#include <stdio.h>
#include "vars_defs_functions.h"


void outputWorld(int gen, CELL **current){

  int i, j;



  char worldfilenamebuf[20];

  
  snprintf(worldfilenamebuf, sizeof(worldfilenamebuf), "data/world%d.dat", gen);
  FILE *fp_world = fopen(worldfilenamebuf, "w");

  for(i=0; i<ROWS; i++){ 
    for(j=0; j<COLS; j++){

      #if DEBUG_LEVEL > 0
      printf("%c", current[i][j].state);
      #endif
      
      fprintf(fp_world, "%c", current[i][j].state);

    }

    #if DEBUG_LEVEL > 0
    printf("\n");
    #endif
    
    fprintf(fp_world, "\n");

  }

  fclose(fp_world);

}
