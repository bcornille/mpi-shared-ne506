/**************************************************************************//*!
 * \file
 * \brief This file will contain the main driver for the Shared Memory parallel
 * Monte Carlo code.
 *
 ******************************************************************************/

// Dependencies and necessary inclusions.
#include <mpi.h>

#include "comms.h"
#include "trans.h"

/* For now we will just make a hard definition of the number of source particles
 * used for the simulation.  This will need to be made flexible in a usable 
 * code. */
#define n_source_parts 100000

//! Main program.
/*!
 * \param argc number of arguments
 * \param argv arguments
 */
int main(int argc, char *argv[])
{
	// Initialize the program based on input.
	ShMemMC_MPI_Init(&argc, &argv);

	ShMemMC_Transport(n_source_parts);

	ShMemMC_MPI_Finalize();

	return 0;
}
