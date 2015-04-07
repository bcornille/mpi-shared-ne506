#ifndef _geoms_h
#define _geoms_h

/***************************************
 *  2nd order analytic surfaces.
 *  F(x,y,z) = a*x^2 + b*y^2 + c*z^2 +
 *  			d*x*y + e*y*z + f*z*x +
 *  			g*x + h*y + i*z + j
 *  Defined where F(x,y,z) = 0
 **************************************/
typedef struct Surface {
	double a;
	double b;
	double c;
	double d;
	double e;
	double f;
	double g;
	double h;
	double i;
	double j;
} Surface

typedef struct Face {
	int sense;
	Surface *surf;
} Face

typedef struct Cell {
	int nfaces;
	Face *faces;
	Material *mat;
} Cell

// Routines
void Geom_Init(char *File_in);

void Default_Geom()

#endif
