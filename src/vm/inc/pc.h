/* `pc.h` - Program counter
 */

#ifndef PC_H
#define PC_H

#define PC_RETURN_DEPTH 0xFFFF

#include <stdlib.h>
#include <stdio.h>

#include "is.h"
#include "fh.h"
#include "bc.h"
#include "helper.h"

typedef unsigned long pc_addr;

/* Address stack structure
 */
typedef struct pc_addr_stk {
	long     size;           // Capacity of stack
	long     ptr;            // Stack pointer
	pc_addr* addresses;      // Stack data
} pc_addr_stk;

/* Program counter structure
 */
typedef struct pc_t {
	pc_addr      limit;   // End of program
	pc_addr      address; // Current address
	pc_addr_stk* stk;     // Address stack
	bc_cont*     line;    // Current instruction
	bc_t*        bc;      // Bytecode container instance
} pc_t;

/* Initalizes program counter, returns pc_t* instance
 * char* - filename of file containing bytecode
 */
pc_t* pc_new(char*);

/* Creates a new address stack.
 *  ns_addr - inital address
 */
pc_addr_stk* pc_addr_stk_new(ns_addr);

/* Frees memory assosiated with pc_t* instance
 */
void pc_del(pc_t*);

/* Frees memory assosiated with pc_addr_stk* instance
 */
void pc_addr_stk_del(pc_addr_stk*);

/* Updates current insturction
 *
 * When called, pc_t->line will reflect pc_t->bc[pc_t->address]
 */
void pc_update(pc_t*);

/* Increment program counter by +-addr
 *  pc_t*   - Program counter instance
 *  pc_addr - Address to increment by
 */
void pc_inc(pc_t*, pc_addr);

/* Branch to specified address.
 *  pc_t*   - Program counter instance
 *  pc_addr - Address to branch to
 */
void pc_branch(pc_t*, pc_addr);

/* Return from previous branch.
 *  pc_t* - Program counter instance
 */
void pc_return(pc_t*);

/* Simply goto that address
 *  pc_t*   - Program counter instance
 *  pc_addr - Address to go to
 */
void pc_goto(pc_t*, pc_addr);

/* For now, a simple function that tests if the address is in range
 */
int pc_safe(pc_t* pc);

#endif // PC_H
