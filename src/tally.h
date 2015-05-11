/*!
 * \file
 * \brief Tally header file.
 */

#ifndef _tally_h
#define _tally_h

#include <mpi.h>

typedef struct XYZMesh {
	int nx;
	int ny;
	int nz;
	MPI_Win xwin;
	double *xbins;
	MPI_Win ywin;
	double *ybins;
	MPI_Win zwin;
	double *zbins;
	MPI_Win tally_win;
	double *tally;
} XYZMesh;

void Default_Tally();
void Tally_Init(char *File_in);

#endif
