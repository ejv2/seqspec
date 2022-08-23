/*
 * seqspec - analyze and continue arbitrary sequences of any order
 * Copyright (C) Ethan Marshall - 2022
 */

#ifndef SEQSPEC_H
#define SEQSPEC_H

#include <stdlib.h>

/* User facing headers
 * Library code *SHOULD NEVER* include this directly
 */

/*
 * Opaque handle to sspec sequence data.
 * Whenever returned as a pointer, it is the caller's responsibility to
 * free as though any other pointer.
 */
typedef struct seqspec sspec_t;

/* Main bulk of the library */
#include "sspec_internal.h"

#endif
