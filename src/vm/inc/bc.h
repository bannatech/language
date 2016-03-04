/* `bc` handles bytecode objects.
 */

#ifndef BC_H
#define BC_H

#include <stdlib.h>
#include <stdio.h>

#include "fh.h"
#include "helper.h"
#include "var.h"

typedef unsigned int bc_addr;

/* 'Bytecode Container'
 */
typedef struct bc_cont {
	bc_addr   real_addr;
	byte_t    op;
	byte_t    mdata;
	byte_t    adata;
	byte_t*   args[3];
	var_cont* varg[3];
	int       sarg[3];
	struct bc_cont* next;
	struct bc_cont* prev;
} bc_cont;

#include "is.h"

/* Handles allocation for new `bc_cont` instances
 */
bc_cont* bc_cont_new(void);

/* Pushes new bc_cont to the chain.
 * bc_cont** - bytecode container
 */
void bc_cont_push(bc_cont**);

/* Deallocates all the things, assuming the arguement is the root.
 *  bc_cont* - bytecode container, root node (hopefully)
 */
void bc_cont_del(bc_cont*);

/* Given a file object, and an instance of `bc_cont` with proper metadata, this
 * function will read arguements into bc_cont.
 */
void get_args(FILE*, bc_cont*);
byte_t* get_byte_arg(FILE*, int*);
byte_t* get_name_arg(FILE*, int*);
byte_t* get_addr_arg(FILE*, int*);
byte_t* get_dync_arg(FILE*, int*);

/* Process arguements into typed & readable data
 *  bc_cont* - bytecode container
 */
void process_args(bc_cont*);

/* Scan to +/- int in bytecode chain
 *  bc_cont* - bytecode container [0]
 *  int      - +/- up/down        [1]
 *
 * -> bc_cont* - Bytecode @param[0]'s location +/- @param[1]
 */
bc_cont* bc_scan(bc_cont*, int);

/* Initiates the first pass to take a raw binary file and translate it into a
 * basic datastructure
 *  char* -> filename
 */
bc_cont* bc_read(char*);

#endif // BC_H
