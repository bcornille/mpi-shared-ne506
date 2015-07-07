/**************************************************************************//*!
 * \file
 * \brief This file will contain the main driver for the Shared Memory parallel
 * Monte Carlo code.
 *
 ******************************************************************************/

// Dependencies and necessary inclusions.
#include <stdio.h>
#include "comms.h"
#include "trans.h"

/* For now we will just make a hard definition of the number of source particles
 * used for the simulation.  This will need to be made flexible in a usable 
 * code. */
// #define n_source_parts 100000

//! Main program.
/*!
 * \param argc number of arguments
 * \param argv arguments
 */
int main(int argc, char *argv[])
{
	// Initialize the program based on input.
	ShMemMC_MPI_Init(argc, argv);

	if(all_rank == 0 && argc == 1) {
		printf("Usage: ShMemMC <nparts> <nmesh> <nsplit>\n");
		printf("Running default calculation with 10 particles and nmesh 10.\n");
	}

	MPI_Barrier(all_comm);
	double timer = -MPI_Wtime();
	ShMemMC_Transport(n_source_parts);
	MPI_Barrier(all_comm);
	timer += MPI_Wtime();

	if(all_rank == 0) {
		printf("Particle transport took %f seconds.\n", timer);
	}

	ShMemMC_MPI_Finalize();

	return 0;
}
