CC=mpicc.mpich
CFLAGS= -c -g -Wall

accum : mpi_accum_test.o
	$(CC) mpi_accum_test.o -o accum

mpi_accum_test.o : mpi_accum_test.c
	$(CC) $(CFLAGS) mpi_accum_test.c

clean :
	rm -f mpi_accum_test.o accum
