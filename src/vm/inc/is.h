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

#include "ins_mdata.h"

#define A_NULL 0
#define A_BYTE 1
#define A_WORD 2
#define A_DYNC 3

#define encode(n, a0, a1, a2) \
	( n << 6 | a0 << 4 | a1 << 2 | a2 );

// This array is populated by inc/is_mdata
byte_t INS_MDATA[256];

/*
 * Takes an opcode, fills metadata about that opcode (given that it exists) in the
 * `bc_cont` structure
 */
void get_opcode(byte_t, bc_cont*);

/*
 * Fills in metadata in @param byte_t.
 * @param[1] is number of params,
 * @param[2] is an array[3] detailing param types
 *
 * For example, given a byte 11011011, it would break down into the following:
 * @param[1] = 3,
 * @param[2] = { 01, 10, 11 }
 */
void get_mdata(byte_t, int*, int*);

/*
 * Sets up the datastructure to quickly queue for data.
 */
void init(void);

void init_mdata(void);

#endif // IS_H
