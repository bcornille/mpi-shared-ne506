#ifndef _comms_h
#define _comms_h

// MPI Communicators.
MPI_Comm all_comm = MPI_COMM_WORLD;	// Complete communicator
MPI_Comm shmem_comm;				// Shared memory communicator

// MPI rank and size variables.
extern int all_rank		// Process rank
extern int all_size		// Total number of processes
extern int shmem_rank	// Process rank in shared memory communicator
extern int shmem_size	// Size of shared memory communicator

#endif
