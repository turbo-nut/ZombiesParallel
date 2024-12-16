#include <stdio.h>
#include "vars_defs_functions.h"

void outputDaySZRD(FILE *fp_daySZRD, int day,
		    long numS,
		    long numZ,
		    long numR,
		    long numD,
		    long numI){
  fprintf(fp_daySZRD," %d %lu %lu %lu %lu %lu\n", day,numS,numZ,numR,numD, numI);
		    #if DEBUG_LEVEL > 1
		    printf(" S: %lu\n Z: %lu\n R: %lu\n D: %lu\n I: %lu\n", numS,numZ,numR,numD, numI);
		    #endif
}
