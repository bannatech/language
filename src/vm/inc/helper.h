/* `helper.h` -> Helper macros/functions
 */

#ifndef HELPER_H
#define HELPER_H

#include <stdio.h>

#define ASSERT(condition, message)\
	if (!(condition))             \
	{                             \
		fprintf(stderr, message); \
		exit(1);                  \
	}

#define SIZE_ASSERT(condition)    \
	if (!(condition))             \
	{                             \
		fprintf(stderr, "address exeeded namespace limit\n"); \
		exit(1);                  \
	}

#define M_ASSERT(x)                                    \
	if (x == NULL)                                     \
	{                                                  \
		fprintf(stderr, "Could not allocate memory\n");\
	}

#define N_ASSERT(x)                         \
	if (x == NULL)                          \
	{                                       \
		fprintf(stderr, "Null Exception\n");\
		exit(1);                            \
	}                                       \

#endif // HELPER_H
