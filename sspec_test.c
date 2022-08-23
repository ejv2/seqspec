/*
 * seqspec - analyze and continue arbitrary sequences of any order
 * Copyright (C) Ethan Marshall - 2022
 */

/* automated test harness */

#include <stdio.h>
#include <stdlib.h>

#include "libsspec.h"

#define LENGTH(x) (sizeof(x) / sizeof(x[0]))

struct test {
	const long seq[50];
	size_t len;
	struct {
		long diff;
		unsigned char order;
		int failure;
	} expects;
};

static const struct test tests[] = {
	/* stock examples */
	{{1, 1, 1}, 3, {.diff = 0, .order = 1}},
	{{1, 2, 3}, 3, {.diff = 1, .order = 1}},
	{{1, 4, 9, 16, 25, 36}, 6, {.diff = 2, .order = 2}},
	{{4, 16, 36, 64, 100}, 5, {.diff = 8, .order = 2}},
	{{1, 8, 27, 64, 125}, 5, {.diff = 6, .order = 3}},

	/* edge cases */
	{{0, 0, 0}, 3, {.diff = 0, .order = 1}},
	{{1, 0, -1, -2}, 4, {.diff = -1, .order = 1}},

	/* failure cases */
	{{-100, -101, 99}, 3, {.failure = 1}},                 /* no obvious sequence */
	{{-1, 2, 2001}, 3, {.failure = 1}},                    /* no obvious sequence */
	{{1, 4, 9}, 3, {.failure = 1}},                        /* buffer exhaustion */
};

void seq_print(const long *seq, size_t len)
{
	putchar('[');
	for (size_t i = 0; i < len; i++) {
		printf("%ld", seq[i]);
		if (i < len - 1) {
			putchar(' ');
		}
	}
	putchar(']');
}

int main(int argc, char **argv)
{
	int fail = 0;

	for (size_t i = 0; i < LENGTH(tests); i++) {
		sspec_t *s = sspec_analyze(tests[i].seq, tests[i].len);
		if (!s) {
			if (tests[i].expects.failure)
				continue;

			printf("[FAIL] %zu failed for input ", i);
			seq_print(tests[i].seq, tests[i].len);
			printf(" (reported error)\n");

			fail++;
			continue;
		}
		if (tests[i].expects.failure) {
			printf("[FAIL] %zu failed for input ", i);
			seq_print(tests[i].seq, tests[i].len);
			printf("(failed to report error :- diff: %d, ord: %d)\n", sspec_diff(s), sspec_ord(s));
			fail++;
			continue;
		}

		if (sspec_diff(s) != tests[i].expects.diff ||
			sspec_ord(s) != tests[i].expects.order) {
			printf("[FAIL] %zu failed for input ", i);
			seq_print(tests[i].seq, tests[i].len);
			printf(" (diff: %d, ord: %d)\n", sspec_diff(s), sspec_ord(s));
			fail++;
		}

		free(s);
	}

	if (fail) {
		printf("[FAIL] %d test(s) failed of %lu\n", fail, LENGTH(tests));
		return 1;
	}

	puts("[PASS]");
	return 0;
}
