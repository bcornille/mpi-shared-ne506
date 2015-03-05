CC=mpicc.mpich
CFLAGS= -c -g -Wall

race : mpi_shmem_race.o
	$(CC) mpi_shmem_race.o -o race

mpi_shmem_race.o : mpi_shmem_race.c
	$(CC) $(CFLAGS) mpi_shmem_race.c

clean :
	rm -f mpi_shmem_race.o race
