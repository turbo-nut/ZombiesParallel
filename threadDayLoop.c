#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include "vars_defs_functions.h"
//extern ints for threads


//using a mutex lock and conditional variable
pthread_mutex_t lock;
pthread_cond_t cond;
int finished;
int finishedThreads;
void* threadDayLoop(void* rank){

  long intRank = (long) rank;

  finishedThreads = 0;

  pthread_mutex_init(&lock, NULL);



  long long startRow = intRank * (ROWS/THREAD_COUNT);
  long long endRow = ((intRank+1) * (ROWS/THREAD_COUNT)) - 1;

  int day = 1;
  int i,j, row, col, numZN, numSN;
  

  long localnumS = 0, localnumZ = 0, localnumR = 0, localnumD = 0, localnumI = 0;


///////////////////////////////////// DAY LOOP /////////////////////////////

  while (day < TOTAL_DAYS) {
    for (row=startRow;row<endRow;row++) {
      for (col=0;col<COLS;col++) {
        switch (current[row][col].state) {
          case 'S':
            numZN = countZombieNeighbours(row,col,current);
            decide_S_to_IorR(row, col, numZN, &localnumS, &localnumI, &localnumR, current, future);
            if (future[row][col].state == 'S') {
              decide_S_to_D(row, col, numZN, &localnumS, &localnumD, current, future);
          }
            break;


          case 'Z':
            numSN = countSusceptibleNeighbours(row,col,current);
            decide_Z_to_D(row,col,numSN,&localnumZ,&localnumD,current,future);
            break;

          case 'I':
            decide_I_to_Z(row,col,&localnumI,&localnumZ,current,future);
            break;

          case 'R':
            decide_R_to_Z(row,col,&localnumR,&localnumZ,current,future);
            break;

          case 'D':
            decide_D_to_Empty(row,col,&localnumD,current,future);
          break;
        }
      }
    }
    // once the threads are finished with each loop, we store it into the global variables
      
    pthread_mutex_lock(&lock);
    finishedThreads++;
    if (finishedThreads == THREAD_COUNT) {
      #if DEBUG_LEVEL > 1
      printf("Threads finished... compiling stats..\n\n");
      printf("Day %d of %d done.\n\n", day, TOTAL_DAYS);
      #endif
      for (i=0;i<ROWS;i++) {
        for (j=0;j<COLS;j++) {
        if (current[i][j].stateChange == 'Y') {
          current[i][j] = future[i][j];
          } 
        }
      }
      finishedThreads = 0;
      pthread_cond_broadcast(&cond);
      #if DEBUG_LEVEL > 1
      printf("Broadcast to threads\n\n");
      #endif
    }
    else{
      while(pthread_cond_wait(&cond,&lock) != 0);
    }
    pthread_mutex_unlock(&lock);
    globalnumS += localnumS;
    globalnumZ += localnumZ;
    globalnumD += localnumD;
    globalnumR += localnumR;
    globalnumI += localnumI;

    #if DEBUG_LEVEL > 1
    printf("End of day loop.\n");
    #endif

    #if DEBUG_LEVEL > 1
    printf("Checking for hang\n");
    #endif
    localnumS = 0, localnumZ = 0, localnumR = 0, localnumD = 0, localnumI = 0;
    #if DEBUG_LEVEL > 1
    printf("Checking for hang again\n");
    #endif

    

  }
  pthread_cond_destroy(&cond);
  return 0;
}








