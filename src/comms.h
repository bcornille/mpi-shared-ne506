/*!
 * \file
 * \brief Communicator header file.
 */
#ifndef _comms_h
#define _comms_h

#include <mpi.h>

// MPI Communicators.
extern MPI_Comm all_comm;	//!< Complete communicator
extern MPI_Comm shmem_comm;	//!< Shared memory communicator

// MPI rank and size variables.
extern int all_rank;	//!< Process rank
extern int all_size;	//!< Total number of processes
extern int shmem_rank;	//!< Process rank in shared memory communicator
extern int shmem_size;	//!< Size of shared memory communicator

// Number of source particles.
extern int n_source_parts;	//!< Number of source particles
extern int nmesh;			//!< Temporary: default mesh size

// Routines.
void ShMemMC_MPI_Init(int argc_cpy, char* argv_cpy[]);
void ShMemMC_MPI_Finalize();

#endif
