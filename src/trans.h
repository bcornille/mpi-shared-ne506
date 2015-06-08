/*!
 * \file
 * \brief Header file for particle transport.
 */

#ifndef _trans_h
#define _trans_h

#include "geoms.h"

typedef struct Particle {
	Point r;
	Vector v_hat;
	Cell *in_cell;
	Surface *on_surf;
	struct Particle *next;
} Particle;

extern Particle *curr_part;

void ShMemMC_Transport(int nparts_gen);

#endif
