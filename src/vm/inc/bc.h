/* `bc` handles bytecode objects.
 */

#ifndef BC_H
#define BC_H

#include <stdlib.h>
#include <stdio.h>

#include "fh.h"
#include "var.h"
#include "helper.h"

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
} bc_cont;

typedef struct bc_t {
	bc_addr   size;
	bc_cont** heap;
} bc_t;

#include "is.h"

/* Handles allocation for new `bc_cont` instances
 */
bc_cont* bc_cont_new(void);

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

/* Reads program into bc_cont instances
 *  FILE*    - File descriptor
 *  bc_addr* - pointer to size variable
 */
bc_cont** bc_read(FILE* f, bc_addr*);

/* Reads program into bc_t instance
 *  char* - filename
 */
bc_t* bc_init(char*);

/* Deletes instance of bc_t*
 */
void bc_del(bc_t*);

#endif // BC_H
