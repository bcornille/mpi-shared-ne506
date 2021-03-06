/***************************************************************************//*!
 * \file
 * \brief This file will hold all the subroutines for general purpose
 * communication.
 *
 * Major functionality of these subroutines include setting up important MPI
 * initialization and variables as well as cleaning up and finalizing MPI for
 * this program.
 *
 * Contents:
 *
 * ShMemMC_MPI_Init - Main routine for initializing MPI for this program.
 *
 * ShMemMC_MPI_Finalize - Main routine for cleaning up variables and MPI for
 * 	this program.
 *
 ******************************************************************************/

// Dependencies and necessary inclusions.
#include <stdlib.h>
#include "rngsets.h"
#include "geoms.h"
#include "source.h"
#include "tally.h"
#include "comms.h"

// Define and initialize all external variables.
MPI_Comm all_comm = MPI_COMM_WORLD;
MPI_Comm shmem_comm;
int all_rank;
int all_size;
int shmem_rank;
int shmem_size;
int n_source_parts;
int nmesh;
int nsplit;

//! Program specific initialization.
/*! 
 * \param argc pointer to number of arguments
 * \param argv pointer to arguments
 */
void ShMemMC_MPI_Init(int argc_cpy, char* argv_cpy[])
{
	if(argc_cpy == 1) {
		n_source_parts = 10;
	} else {
		n_source_parts = atoi(argv_cpy[1]);
	}

	if(argc_cpy <= 2) {
		nmesh = 10;
	} else {
		nmesh = atoi(argv_cpy[2]);
	}

	if(argc_cpy <= 3) {
		nsplit = 1;
	} else {
		nsplit = atoi(argv_cpy[3]);
	}

	// Standard MPI Initialization bits.
	MPI_Init(&argc_cpy, &argv_cpy);
	MPI_Comm_rank(all_comm, &all_rank);
	MPI_Comm_size(all_comm, &all_size);

	// Setting up shared memory communicator and ranks.
	/*MPI_Comm_split_type(all_comm, MPI_COMM_TYPE_SHARED, 0, MPI_INFO_NULL,
			&shmem_comm);*/
	MPI_Comm_split(all_comm, all_rank%nsplit, 0, &shmem_comm);
	MPI_Comm_rank(shmem_comm, &shmem_rank);
	MPI_Comm_size(shmem_comm, &shmem_size);

	if(argc_cpy <= 4) {
		Default_Geom();		// Use the default geometry.
	} else {
		Geom_Init(argv_cpy[4]);	/* Generate the geometry based on the input
									 * file. */
	}

	if(argc_cpy <= 4) {
		Default_Source();
	} else {
		Source_Init(argv_cpy[4]);
	}

	if(argc_cpy <= 4) {
		Default_Tally();
	} else {
		Tally_Init(argv_cpy[4]);
	}

	init_sprng(SEED,SPRNG_DEFAULT,0);

	return;
}

//! Clean up various portions of the code.
/*!
 * Allocated arrays in various code segments:
 *  1. geoms.c :
 *    1. #surfs
 *    2. #cells
 *      1. Cell#faces
 */
void ShMemMC_MPI_Finalize()
{
	// Dismantle geometry.
	Free_Geom();
	Free_Tallies();

	// Finalize MPI.
	MPI_Finalize();

	return;
}
