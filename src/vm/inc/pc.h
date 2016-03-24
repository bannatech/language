/* `pc.h` - Program counter
 */

#ifndef PC_H
#define PC_H

#define PC_RETURN_DEPTH 0xFF

#include <stdlib.h>
#include <stdio.h>

#include "is.h"
#include "fh.h"
#include "bc.h"
#include "helper.h"

typedef unsigned short int pc_addr;

typedef struct pc_addr_stk {
	size_t   size;
	int      ptr;
	pc_addr* addresses;
} pc_addr_stk;

/* pc_t structure
 */
typedef struct pc_t {
	pc_addr      limit;
	pc_addr      address;
	pc_addr_stk* stk;
	bc_cont*     line;
	bc_t         program;
} pc_t;

/* Initalizes program counter, returns pc_t* instance
 * char* - filename of file containing bytecode
 */
pc_t* pc_new(char*);

void pc_read(char*, pc_t*);

pc_addr_stk* pc_addr_stk_new(ns_addr);

/* Frees memory assosiated with pc_t* instance
 */
void pc_del(pc_t*);
void pc_addr_stk_del(pc_addr_stk*);

/* Pushes instruction to heap
 */
void pc_push(pc_t*, bc_cont*);

/* Updates program counter on changes in address
 */
void pc_update(pc_t*);

/* Increment program counter by amount in pc_addr
 */
void pc_inc(pc_t*, pc_addr);

/* Branch to addr
 */
void pc_branch(pc_t*, pc_addr);

/* Return from branch
 */
void pc_return(pc_t*);

/* For now, a simple function that returns true if the next instruction is not
 * NULL.
 */
int pc_safe(pc_t* pc);

#endif // PC_H
