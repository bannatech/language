/*
 `bc` handles bytecode objects.
*/

#ifndef FH_H
#define FH_H

#include <stdlib.h>
#include <stdio.h>

/*
 'Bytecode Container'
*/
typedef struct bc_cont {
	unsigned char   op;
	unsigned char*  args[3];
	unsigned char   mdata;
	struct bc_cont* next;
} bc_cont;

/*
 Handles allocation for new `bc_cont` instances
*/
bc_cont* bc_cont_new(void);

/*
 Deallocates all the things, assuming the arguement is the root.
*/
void bc_cont_del(bc_cont*);

/*
 Given a file object, and an instance of `bc_cont` with proper metadata, this
 function will read arguements 
*/
void get_args(FILE**, long*, bc_cont**);
// meta-functions
unsigned char get_byte_arg(FILE**, long*);
unsigned char get_word_arg(FILE**, long*);
unsigned char get_dync_arg(FILE**, long*);

/*
 Takes a FILE arguement, reads, returns size of file.
 Useful \w loops.
*/
long read_size(FILE**, char*);

/*
 Initiates the first pass to take a raw binary file and translate it into a
 basic datastructure
*/
bc_cont* bc_read(char* fname);

#endif // FH_H
