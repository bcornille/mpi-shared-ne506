CC=mpicxx
CFLAGS= -c -g -Wall
INCLUDE= -I/home/bcornille/usr/sprng/sprng5/include
SPRNGPATH=/home/bcornille/usr/sprng/sprng5/lib
LIBS= -lsprng

sprng_mpi_simple : sprng_mpi_HelloWorld.o
	$(CC) $(INCLUDE) sprng_mpi_HelloWorld.o -o sprng_mpi_simple -L$(SPRNGPATH) $(LIBS)

sprng_mpi_HelloWorld.o : sprng_mpi_HelloWorld.c
	$(CC) $(INCLUDE) $(CFLAGS) sprng_mpi_HelloWorld.c 

clean :
	rm -f sprng_mpi_HelloWorld.o sprng_mpi_simple
