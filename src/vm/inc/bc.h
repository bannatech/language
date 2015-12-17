/*
 * `bc` handles bytecode objects.
 */

#ifndef BC_H
#define BC_H

#include <stdlib.h>
#include <stdio.h>

#include "fh.h"

/*
 * 'Bytecode Container'
 */
typedef struct bc_cont {
	byte_t   op;
	byte_t*  args[3];
	byte_t   mdata;
	struct bc_cont* next;
} bc_cont;

#include "is.h"

/*
 * Handles allocation for new `bc_cont` instances
 */
bc_cont* bc_cont_new(void);

/*
 * Pushes new bc_cont to the chain.
 */
bc_cont* bc_cont_push(bc_cont*);

/*
 * Deallocates all the things, assuming the arguement is the root.
 */
void bc_cont_del(bc_cont*);

/*
 * Given a file object, and an instance of `bc_cont` with proper metadata, this
 * function will read arguements into bc_cont.
 */
void get_args(FILE*, bc_cont*);
byte_t* get_byte_arg(FILE*);
byte_t* get_word_arg(FILE*);
byte_t* get_dync_arg(FILE*);

/*
 * Initiates the first pass to take a raw binary file and translate it into a
 * basic datastructure
 */
bc_cont* bc_read(char* fname);

#endif // BC_H
