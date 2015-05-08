CC=/usr/local/openmpi/bin/mpicc
CFLAGS= -c -O0 -g -Wall

ll : mpi_shmem_ll.o
	$(CC) mpi_shmem_ll.o -o ll

clean :
	rm -f mpi_shmem_ll.o ll
