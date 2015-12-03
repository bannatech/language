/*
 `is` holds the instruction set specification.

 Anything having to do with getting information about a given instruction will
 be handled by this file.
*/

#ifndef IS_H
#define IS_H

#include <stdlib.h>

#include "bc.h"

#define A_NULL 0
#define A_BYTE 1
#define A_WORD 2
#define A_DYNM 3

/*
 Takes an opcode, fills metadata about that opcode (given that it exists) in the
 `bc_cont` structure
*/
void get_opcode(char, bc_cont**);


#endif // IS_H
