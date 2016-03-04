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

typedef struct pc_stk {
	pc_addr address;
	struct pc_stk* next;
} pc_stk;

/* pc_t structure
 *
 * bc_cont* root - First instruction
 * bc_cont* line - Current instruction
 * pc_stk*  stk  - Address stack
 */
typedef struct pc_t {
	bc_cont* root;
	bc_cont* line;
	pc_stk*  stk;
} pc_t;

/* Initalizes program counter, returns pc_t* instance
 * char* - filename of file containing bytecode
 */
pc_t* pc_new(char*);
pc_stk* pc_stk_new(ns_addr);

/* Frees memory assosiated with pc_t* instance
 */
void pc_del(pc_t*);
void pc_stk_del(pc_stk*);

/* Updates program counter on changes
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

#endif // PC_H
