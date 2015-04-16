/**************************************************************************//*!
 * \file
 * \brief This file will contain the main driver for the Shared Memory parallel
 * Monte Carlo code.
 *
 ******************************************************************************/

// Dependencies and necessary inclusions.
#include <mpi.h>

#define SIMPLE_SPRNG
#define USE_MPI
#include "sprng.h"

/* While it is convenient to have a consistent seed for reproducible calculations,
 * one should generate a unique seed for production runs (usually from system time).
 * This capability should be added later. */
#define SEED 987654321

#include "comms.h"

//! Main program.
/*!
 * \param argc number of arguments
 * \param argv arguments
 */
int main(int argc, char *argv[])
{
	// Initialize the program based on input.
	ShMemMC_MPI_Init(&argc, &argv);

	ShMemMC_MPI_Finalize();

	return 0;
}
