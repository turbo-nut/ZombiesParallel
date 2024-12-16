#include "timer.h"
#include "vars_defs_functions.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int day; // track the day
FILE *fp_daySZRD;
// Track quantities of S/Z/R/D
long globalnumS = 0;
long globalnumZ = 0;
long globalnumR = 0;
long globalnumD = 0;
long globalnumI = 0;


  pthread_cond_t cond;
  pthread_mutex_t lock;
// redefine cells
CELL **current, **future;
int main() {



  long thread;

  globalnumS = 0;
  globalnumZ = 0;
  globalnumR = 0;
  globalnumD = 0;
  globalnumI = 0;
  // give an address and allocate memory to the threads
  pthread_t *thread_handles = malloc(THREAD_COUNT * sizeof(pthread_t));

  // track start and end time, use to get elapsed time
  double startTime, endTime, runTime;

  // get the starting time
  GET_TIME(startTime);

  // allocating memory to the cells
  current = (CELL **)malloc(ROWS * sizeof(CELL *));
  future = (CELL **)malloc(ROWS * sizeof(CELL *));

  for (int i = 0; i < ROWS; i++) {
    current[i] = (CELL *)malloc(COLS * sizeof(CELL));
    future[i] = (CELL *)malloc(COLS * sizeof(CELL));
  }

#if DEBUG_LEVEL > 1
  printf("Memory allocated to cells.\n\n\n");
#endif

  // open the file for writing
  fp_daySZRD = fopen("data/daySZRD.dat", "w");

#if DEBUG_LEVEL > 1
  printf("File Ready...\n\n\n");
#endif

  // generate seed
  srand((unsigned int)time(NULL));
#if DEBUG_LEVEL > 1
  printf("Seed Generated...\n\n\n");
#endif

  // start world
  initialiseWorld(current, future, &globalnumS, &globalnumZ);
#if DEBUG_LEVEL > 1
  printf("World Initialised.\n\n\n");
#endif

  pthread_mutex_init(&lock, NULL);


  outputDaySZRD(fp_daySZRD, day, globalnumS, globalnumZ, globalnumR, globalnumD,
                globalnumI);
  outputWorld(day, current);

  // creating threads
  for (thread = 0; thread < THREAD_COUNT; thread++) {
    pthread_create(&thread_handles[thread], NULL, threadDayLoop,
                   (void *)thread);
    printf("Thread %ld: created. Running...\n", thread);
  }

  // join the threads
  for (thread = 0; thread < THREAD_COUNT; thread++) {
    printf("Thread %ld: joining.\n", thread);
    pthread_join(thread_handles[thread], NULL);
  }

  // we're freeing the memory to prevent memory leaks
  // freeing cells, then the file, then threads
  free(current);
  free(future);
  fclose(fp_daySZRD);
  free(thread_handles);

  // get the total runtime of the program
  GET_TIME(endTime);
  runTime = endTime - startTime;
  printf("Total runtime: %f\n", runTime);
}
