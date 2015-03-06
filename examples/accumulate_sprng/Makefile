CC=mpicxx.mpich
CFLAGS= -c -g -Wall
INCLUDE= -I/home/bcornille/usr/sprng/sprng5/include
SPRNGPATH=/home/bcornille/usr/sprng/sprng5/lib
LIBS= -lsprng

mpi_accum_sprng : mpi_accum_sprng.o
	$(CC) $(INCLUDE) mpi_accum_sprng.o -o accum_sprng -L$(SPRNGPATH) $(LIBS)

mpi_accum_sprng.o : mpi_accum_sprng.c
	$(CC) $(INCLUDE) $(CFLAGS) mpi_accum_sprng.c 

clean :
	rm -f mpi_accum_sprng.o accum_sprng
