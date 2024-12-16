#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include "vars_defs_functions.h"

void* threadDayLoop(void* rank){

  long intRank = (long) rank;
  int finishedThreads;


  long long startRow = intRank * (ROWS/THREAD_COUNT);
  long long endRow = ((intRank+1) * (ROWS/THREAD_COUNT)) - 1;

  int day;
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
    #if DEBUG_LEVEL > 1
    printf("Mutex lock.\n Day: %d.\n Thread Finished.\n", day);
    #endif
    globalnumS += localnumS;
    globalnumZ += localnumZ;
    globalnumD += localnumD;
    globalnumR += localnumR;
    globalnumI += localnumI;
    #if DEBUG_LEVEL > 1
    printf("Global var update.\n");
    #endif
    #if DEBUG_LEVEL > 1
    printf("Finished Threads: %d\n", finishedThreads);
    #endif
    if (finishedThreads == THREAD_COUNT) {
      day++;
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
      pthread_cond_broadcast(&cond);
      #if DEBUG_LEVEL > 1
      printf("Broadcast to threads\n\n");
      #endif
      finishedThreads = 0;
    }
    else{
      while(pthread_cond_wait(&cond,&lock) != 0);
    }

    pthread_mutex_unlock(&lock);
    localnumS = 0, localnumZ = 0, localnumR = 0, localnumD = 0, localnumI = 0;

    

  }
}








