/*
 `is` holds the instruction set specification.

 Anything having to do with getting information about a given instruction will
 be handled by this file.
*/

#ifndef IS_H
#define IS_H

#include <stdlib.h>

#include "bc.h"
#include "fh.h"

#define A_NULL 0
#define A_BYTE 1
#define A_WORD 2
#define A_DYNC 3

#define encode(n, a0, a1, a2) \
	( n << 6 | a0 << 4 | a1 << 2 | a2 );

// This array is populated by inc/is_mdata
byte_t INS_MDATA[256];

/*
 Takes an opcode, fills metadata about that opcode (given that it exists) in the
 `bc_cont` structure
*/
void get_opcode(byte_t, bc_cont**);

void get_mdata(byte_t, int*, int*);

void init(void);

void init_mdata(void);

#endif // IS_H
