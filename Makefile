testOutput: outputWorld.o countSusceptibleNeighbours.o countZombieNeighbours.o decide_D_to_Empty.o decide_R_to_Z.o decide_S_to_D.o decide_S_to_IorR.o decide_Z_to_D.o decide_I_to_Z.o initialiseWorld.o outputDaySZRD.o parallel.o threadDayLoop.o
	gcc  -Wall outputWorld.o countSusceptibleNeighbours.o countZombieNeighbours.o decide_D_to_Empty.o decide_R_to_Z.o decide_S_to_D.o decide_S_to_IorR.o decide_I_to_Z.o decide_Z_to_D.o initialiseWorld.o outputDaySZRD.o parallel.o threadDayLoop.o -o testOutput -lpthread

parallel.o: parallel.c
	gcc -Wall -c parallel.c 
outputWorld.o: outputWorld.c
	gcc -c outputWorld.c
countSusceptibleNeighbours.o: countSusceptibleNeighbours.c
	gcc -c countSusceptibleNeighbours.c
countZombieNeighbours.o: countZombieNeighbours.c
	gcc -c countZombieNeighbours.c
decide_D_to_Empty.o: decide_D_to_Empty.c
	gcc -c decide_D_to_Empty.c
decide_I_to_Z.o: decide_I_to_Z.c
	gcc -c decide_I_to_Z.c
decide_R_to_Z.o: decide_R_to_Z.c
	gcc -c decide_R_to_Z.c
decide_S_to_D.o: decide_S_to_D.c
	gcc -c decide_S_to_D.c
decide_S_to_IorR.o: decide_S_to_IorR.c
	gcc -c decide_S_to_IorR.c
decide_Z_to_D.o: decide_Z_to_D.c
	gcc -c decide_Z_to_D.c
initialiseWorld.o: initialiseWorld.c
	gcc -c initialiseWorld.c
outputDaySZRD.o: outputDaySZRD.c
	gcc -c outputDaySZRD.c
threadDayLoop.o: threadDayLoop.c
	gcc -c threadDayLoop.c
clean: 
	rm -f *.o ./data/*.dat
