#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include "vars_defs_functions.h"

void* threadDayLoop(void* rank){

  long numRank = (long) rank;


  long long startRow = numRank * (ROWS/THREAD_COUNT);
  long long endRow = ((numRank+1) * (ROWS/THREAD_COUNT));

  int i,j, row, col, numZN, numSN;
  

  long localnumS, localnumZ, localnumR, localnumD, localnumI;


///////////////////////////////////// DAY LOOP /////////////////////////////

  while (day < TOTAL_DAYS) {
    localnumS = 0;
    localnumZ = 0;
    localnumR = 0;
    localnumD = 0;
    localnumI = 0;
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
    // we then set the lock so that only 1 can actually update at a time
    //
    //once the thread is finished with their loop they check if they're able to access the barrier
    //if not they wait until the last thread is finished
    //
    //the last thread will then make changes to each of the cells, and then output the world
    //i'm using pthreads_cond_t from Pacheco's book, ch 4.8.
    pthread_mutex_lock(&lock);
    finishedThreads++;
    globalnumS += localnumS;
    globalnumZ += localnumZ;
    globalnumD += localnumD;
    globalnumR += localnumR;
    globalnumI += localnumI;
    if (finishedThreads == THREAD_COUNT) {
      day++;
      #if DEBUG_LEVEL > 1
      printf("Thread %ld finished... compiling stats..\n\n", numRank);
      printf("Day %d of %d done.\n\n", day, TOTAL_DAYS);
      #endif
      for (i=0;i<ROWS;i++) {
        for (j=0;j<COLS;j++) {
        if (current[i][j].stateChange == 'Y') {
          current[i][j] = future[i][j];
          } 
        }
      }
      outputDaySZRD(fp_daySZRD, day, globalnumS, globalnumZ, globalnumR, globalnumD, globalnumI);
      if (day%WORLD_OUTPUT_INTERVAL == 0) {
      outputWorld(day,current);
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

    

  }
  return 0;
}








