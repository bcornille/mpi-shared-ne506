CC=mpic++
CFLAGS=-g -O0 -Wall
INCPATH=-I/home/bcornille/usr/sprng/sprng5/include
LIBPATH=-L/home/bcornille/usr/sprng/sprng5/lib
LIBS=-lm -lsprng

OBJS=comms.o geoms.o source.o trans.o

default: ShMemMC_MPI

ShMemMC_MPI: ShMemMC_MPI.o $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(LIBPATH) $(LIBS)

ShMemMC_MPI.o: ShMemMC_MPI.c $(OBJS) comms.h
	$(CC) $(CFLAGS) -c $(INCPATH) $< -o $@

comms.o: comms.h source.h geoms.h

geoms.o: geoms.h comms.h dbg.h

source.o: source.h dbg.h

source.h: trans.h

trans.o: trans.h

trans.h: geoms.h

.PHONY: clean
clean:
	-rm -f *.o ShMemMC_MPI
