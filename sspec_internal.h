/*
 * seqspec - analyze and continue arbitrary sequences of any order
 * Copyright (C) Ethan Marshall - 2022
 */

#ifndef SEQSPEC_INTERNAL_H
#define SEQSPEC_INTERNAL_H

/*
 * Analyzes a sequence to find the order and differences.
 * If seq is NULL or of length < 2, NULL is returned.
 * If the properties of seq could not be determined in 255 iterations,
 * NULL is returned.
 */
sspec_t *sspec_analyze(const long *seq, size_t len);
int sspec_diff(sspec_t *spec);
unsigned char sspec_ord(sspec_t *spec);

#endif
