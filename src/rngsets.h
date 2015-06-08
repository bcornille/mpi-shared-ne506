/*!
 * \file
 * \brief Random number generator settings header file.
 */
#ifndef _rngsets_h
#define _rngsets_h

#define SIMPLE_SPRNG
#define USE_MPI
#include <sprng.h>

/* While it is convenient to have a consistent seed for reproducible
 * calculations, one should generate a unique seed for production runs (usually
 * from system time).  This capability should be added later. */
#define SEED 987654321

#endif
