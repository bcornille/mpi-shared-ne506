CC=mpic++
CFLAGS=-O3 -Wall
INCPATH=-I/home/bcornille/usr/sprng/sprng5/include
LIBPATH=-L/home/bcornille/usr/sprng/sprng5/lib
LIBS=-lm -lsprng

OBJS=comms.o geoms.o materials.o source.o tally.o trans.o

default: ShMemMC_MPI

ShMemMC_MPI: ShMemMC_MPI.o $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(LIBPATH) $(LIBS)

ShMemMC_MPI.o: ShMemMC_MPI.c $(OBJS) comms.h Makefile

comms.o: comms.c comms.h tally.h source.h geoms.h rngsets.h Makefile
	$(CC) $(CFLAGS) -c $(INCPATH) $< -o $@

geoms.o: geoms.c geoms.h comms.h dbg.h Makefile

geoms.h: materials.h Makefile

materials.o: materials.c geoms.h rngsets.h Makefile
	$(CC) $(CFLAGS) -c $(INCPATH) $< -o $@

source.o: source.c source.h dbg.h Makefile

source.h: trans.h Makefile

tally.o: tally.c tally.h trans.h comms.h dbg.h Makefile

trans.o: trans.c trans.h tally.h source.h rngsets.h Makefile
	$(CC) $(CFLAGS) -c $(INCPATH) $< -o $@

trans.h: geoms.h Makefile

.PHONY: clean
clean:
	-rm -f *.o ShMemMC_MPI
