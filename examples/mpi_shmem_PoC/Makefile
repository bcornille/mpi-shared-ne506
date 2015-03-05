CC=mpicc.mpich
CFLAGS= -c -g -Wall

hello : mpi_shmem_HelloWorld.o
	$(CC) mpi_shmem_HelloWorld.o -o hello

mpi_shmem_HelloWorld.o : mpi_shmem_HelloWorld.c
	$(CC) $(CFLAGS) mpi_shmem_HelloWorld.c

clean :
	rm -f mpi_shmem_HelloWorld.o hello
