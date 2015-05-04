/***************************************************************************//*!
 * \file
 * \brief This file will hold all routines related to the source definition.
 *
 * 
 ******************************************************************************/

#include <stdlib.h>
#include "dbg.h"
#include "source.h"

Point (*Sample_Position)();
Vector (*Sample_Direction)();
Cell *(*Source_Cell)(Point r_p);
Surface *(*Source_Surface)();

Point Default_Position()
{
	return (Point){0,0,1};
}

Vector Default_Direction()
{
	return (Vector){0,0,-1};
}

Cell *Default_Cell(Point r_p)
{
	return &cells[0];
}

Surface *Default_Surface()
{
	return &surfs[0];
}

void Default_Source()
{
	Sample_Position = Default_Position;
	Sample_Direction = Default_Direction;
	Source_Cell = Default_Cell;
	Source_Surface = Default_Surface;
}

void Source_Init(char *File_in)
{
	log_info("Source definition based on input is not currently available.");
	exit(1);
}


Particle *Source_Particle()
{
	Particle *new_part = (Particle*)malloc(sizeof(Particle));
	check(new_part != NULL, "Could not allocate new particle.\n");

	new_part->r = Sample_Position();
	new_part->v_hat = Sample_Direction();
	new_part->in_cell = Source_Cell(new_part->r);
	new_part->on_surf = Source_Surface();
	new_part->next = NULL;

	return new_part;

error:
	exit(1);
}
