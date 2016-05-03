#include <stdlib.h>
#include <stdio.h>

#include "pc.h"

#include "is.h"
#include "fh.h"
#include "bc.h"
#include "helper.h"

/* Initalizes program counter, returns pc_t* instance
 * char* - filename of file containing bytecode
 */
pc_t* pc_new(char* fname)
{
	N_ASSERT(fname, "pc_new\n");

	pc_t* pc = (pc_t*)malloc(sizeof(pc_t));
	M_ASSERT(pc);
	// Make a new address stack and set its inital address to 0
	pc->stk = pc_addr_stk_new(0);
	// Make sure the inital address is 0
	pc_branch(pc, 0);
	// Read the program specified
	pc->bc = bc_init(fname);
	// Update the program counter.
	pc_update(pc);

	N_ASSERT(pc->line, "Error in creating new program counter\n");

	return pc;
}

/* Creates a new address stack.
 *  ns_addr - inital address
 */
pc_addr_stk* pc_addr_stk_new(ns_addr address)
{
	pc_addr_stk* new = (pc_addr_stk*)malloc(sizeof(pc_addr_stk));
	M_ASSERT(new);

	new->addresses = (pc_addr*)malloc(sizeof(pc_addr)*PC_RETURN_DEPTH);
	M_ASSERT(new->addresses);

	new->ptr = 0;
	new->size = PC_RETURN_DEPTH;
	new->addresses[new->ptr] = address;

	return new;
}

/* Frees memory assosiated with pc_t* instance
 */
void pc_del(pc_t* pc)
{
	N_ASSERT(pc, "pc_del\n");
	N_ASSERT(pc->stk, "pc_del\n");
	N_ASSERT(pc->bc, "pc_del\n");

	// Free the address stack
	pc_addr_stk_del(pc->stk);
	// Free the program
	bc_del(pc->bc);

	free(pc);
}

/* Frees memory assosiated with pc_addr_stk* instance
 */
void pc_addr_stk_del(pc_addr_stk* stk)
{
	N_ASSERT(stk, "pc_addr_stk_del\n");
	N_ASSERT(stk->addresses, "pc_addr_stk_del\n");

	free(stk->addresses);
	free(stk);
}

/* Updates current insturction
 *
 * When called, pc_t->line will reflect pc_t->bc[pc_t->address]
 */
void pc_update(pc_t* pc)
{
	N_ASSERT(pc, "pc_update\n");
	ASSERT((pc->address < (pc->bc->size + 1)), "Address out of range\n");
	// Update the pointer
	pc->line = pc->bc->heap[pc->address];
}

/* Increment program counter by +-addr
 *  pc_t*   - Program counter instance
 *  pc_addr - Address to increment by
 */
void pc_inc(pc_t* pc, pc_addr addr)
{
	N_ASSERT(pc, "pc_inc\n");
	// Increment pc->address by addr
	pc->address = pc->address + addr;
}

/* Branch to specified address.
 *  pc_t*   - Program counter instance
 *  pc_addr - Address to branch to
 */
void pc_branch(pc_t* pc, pc_addr address)
{
	N_ASSERT(pc, "pc_branch\n");
	// Is there space in the address stack?
	ASSERT(((pc->stk->ptr + 1) < pc->stk->size), "Address Stack Overflow\n");

	// Push the current address on to the stack
	pc->stk->addresses[pc->stk->ptr] = pc->address;

	// Increment the stack pointer
	pc->stk->ptr = pc->stk->ptr + 1;

	// Set the current address to the branching address
	pc->address = address;
}

/* Return from previous branch.
 *  pc_t* - Program counter instance
 */
void pc_return(pc_t* pc)
{
	N_ASSERT(pc, "pc_return\n");
	// Is the stack pointer in range?
	ASSERT(((pc->stk->ptr - 1) > 0), "Address Stack Underflow\n");

	// Decrement the stack pointer
	pc->stk->ptr = pc->stk->ptr - 1;

	// Pop the stack to pc->address
	pc->address = pc->stk->addresses[pc->stk->ptr];
}

/* Simply goto that address
 *  pc_t    - Program counter instance
 *  pc_addr - Address to branch to
 */
void pc_goto(pc_t* pc, pc_addr addr)
{
	N_ASSERT(pc, "pc_goto\n");
	// Do I really need to comment?
	pc->address = addr;
}

/* For now, a simple function that tests if the address is in range
 */
int pc_safe(pc_t* pc)
{
	// If the address is in range return true, if out of range return false
	int rv = (pc->address >= pc->bc->size) ? 0 : 1;
	return rv;
}

