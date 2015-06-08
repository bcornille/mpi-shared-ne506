/*!
 * \file
 * \brief Tally header file.
 */

#ifndef _tally_h
#define _tally_h

#include <mpi.h>

typedef enum Dir {X = 0, Y = 1, Z = 2} Dir;

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

typedef struct Indices_3D {
	int i;
	int j;
	int k;
} Indices_3D;

void Default_Tally();
void Tally_Init(char *File_in);
void Score_Tallies(Point r_0, Point r_1);
void Free_Tallies();

#endif
