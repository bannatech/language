/* `pc.h` - Program counter
 */

#ifndef PC_H
#define PC_H

#include <stdlib.h>
#include <stdio.h>

#include "bc.h"
#include "is.h"
#include "fh.h"
#include "helper.h"

typedef unsigned short int pc_addr;

typedef struct pc_t {
	bc_cont* root;
	bc_cont* line;
	pc_addr  address;
} pc_t;

/* Initalizes program counter
 * char* is filename of file containing bytecode
 */
pc_t* pc_new(char*);

/* Frees memory assosiated with pc_t* instance
 */
void pc_del(pc_t*);

/* Updates program counter on changes
 */
void pc_update(pc_t*);

/* Increment program counter by amount in pc_addr
 */
void pc_inc(pc_t*, pc_addr);

/* Branch
 */
void pc_branch(pc_t*, pc_addr);

#endif // PC_H
