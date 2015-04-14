CC=mpicxx
CFLAGS=-g -Wall
INCPATH=-I/home/bcornille/usr/sprng/sprng5/include
LIBPATH=-L/home/bcornille/usr/sprng/sprng5/lib
LIBS=-lsprng

default: ShMemMC_MPI

ShMemMC_MPI: ShMemMC_MPI.o comms.o geoms.o
	$(CC) $(CFLAGS) $^ -o $@ $(LIBPATH) $(LIBS)

ShMemMC_MPI.o: ShMemMC_MPI.c comms.o geoms.o
	$(CC) $(CFLAGS) -c $(INCPATH) $< -o $@

comms.o: comms.h

geoms.o: geoms.h

comms.h: geoms.h

.PHONY: clean
clean:
	-rm -f *.o ShMemMC_MPI
