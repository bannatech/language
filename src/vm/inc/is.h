/*
 `is` holds the instruction set specification.

 Anything having to do with getting information about a given instruction will
 be handled by this file.
*/

#ifndef IS_H

#include "ins_mdata.h"
#include "bc.h"
#include "fh.h"

// This array is populated by inc/is_mdata.h
byte_t INS_MDATA[0xFF];

/* Takes an opcode, fills metadata about that opcode (given that it exists) in
 * the `bc_cont` structure
 *  byte_t   - opcode
 *  bc_cont* - Bytecode instruction
 */
void get_opcode(byte_t, bc_cont*);

/* Fills in metadata in @param byte_t.
 * byte_t - un-expanded metadata
 * int*   - is number of params          [0]
 * int*   - int[3] detailing param types [1]
 *
 * For example, given a byte 11011011, it would break down into the following:
 * @param[1] = 3,
 * @param[2] = { 01, 10, 11 }
 */
void get_mdata(byte_t, int*, int*);

/* Sets up the datastructure to quickly queue for data.
 */
void init_mdata(void);

#endif // IS_H
