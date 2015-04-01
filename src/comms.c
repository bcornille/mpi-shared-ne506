/*******************************************************************************
 * This file will hold all the subroutines for general purpose communication.
 * Major functionality of these subroutines include setting up important MPI
 * initialization and variables as well as cleaning up and finalizing MPI for
 * this program.
 *
 * Contents:
 *
 *
 *
 ******************************************************************************/

// Dependencies and necessary inclusions.
#include <mpi.h>
#include "comms.h"

// Program specific initialization.
void ShMemMC_MPI_Init(int *argc, char* **argv)
{
	// Standard MPI Initialization bits.
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(all_comm, all_rank);
	MPI_Comm_size(all_comm, all_size);

	// Setting up shared memory communicator and ranks.
	MPI_Comm_split_type(all_comm, MPI_COMM_TYPE_SHARED, 0, MPI_INFO_NULL, &shmem_comm);
	MPI_Comm_rank(shmem_comm, shmem_rank);
	MPI_Comm_size(shmem_comm, shmem_size);
}
