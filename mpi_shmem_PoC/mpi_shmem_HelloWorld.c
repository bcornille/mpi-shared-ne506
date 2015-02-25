#include <stdio.h>
#include "mpi.h"

int main(int argc, char **argv[])
{
	// This block initializes MPI and defines rank and size in the global communicator.
	MPI_Init(&argc, &argv);
	int r, s;
	MPI_comm comm = MPI_COMM_WORLD;
	MPI_Comm_rank(comm, &r);
	MPI_Comm_size(comm, &s);

	// This block defines rankd and size in the shared memory communicator.
	MPI_comm shmcomm;
	MPI_Comm_split_type(comm, MPI_COMM_TYPE_SHARED, 0, MPI_INFO_NULL, &shmcomm);
	int sr, ss;
	MPI_Comm_size(shmcomm, &ss);
	MPI_Comm_rank(shmcomm, &rs);

	printf("Hello from processor %d.  I have rank %d in my shared memory group.", &r, &rs);

	MPI_Finalize();
	return 0;
}
