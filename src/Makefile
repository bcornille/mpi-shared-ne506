CC=mpic++
CFLAGS=-O3 -Wall
INCPATH=-I/home/bcornille/usr/sprng/sprng5/include
LIBPATH=-L/home/bcornille/usr/sprng/sprng5/lib
LIBS=-lm -lsprng

OBJS=comms.o geoms.o source.o trans.o materials.o

default: ShMemMC_MPI

ShMemMC_MPI: ShMemMC_MPI.o $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(LIBPATH) $(LIBS)

ShMemMC_MPI.o: ShMemMC_MPI.c $(OBJS) comms.h Makefile

comms.o: comms.c comms.h source.h geoms.h rngsets.h
	$(CC) $(CFLAGS) -c $(INCPATH) $< -o $@

geoms.o: geoms.c geoms.h comms.h dbg.h

geoms.h: materials.h

materials.o: materials.c geoms.h rngsets.h
	$(CC) $(CFLAGS) -c $(INCPATH) $< -o $@

source.o: source.c source.h dbg.h

source.h: trans.h

trans.o: trans.c trans.h rngsets.h
	$(CC) $(CFLAGS) -c $(INCPATH) $< -o $@

trans.h: geoms.h

.PHONY: clean
clean:
	-rm -f *.o ShMemMC_MPI
