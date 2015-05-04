/*!
 * \file
 * \brief Header file for materials.
 */

#ifndef _materials_h
#define _materials_h

typedef Vector (*Scatter)(Vector v);

typedef struct Material {
	char* name;
	double lac;
	Scatter *scat_func;
} Material;

#endif
