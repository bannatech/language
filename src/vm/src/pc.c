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

	pc->stk = pc_addr_stk_new(0);

	pc->program = bc_init(fname);

	pc_update(pc);

	N_ASSERT(pc->line, "Error in creating new program counter\n");

	return pc;
}

pc_addr_stk* pc_addr_stk_new(ns_addr address)
{
	pc_addr_stk* new = (pc_addr_stk*)malloc(sizeof(pc_addr_stk));
	M_ASSERT(new);

	new->addresses = (pc_addr*)malloc(sizeof(pc_addr)*PC_RETURN_DEPTH);
	M_ASSERT(new->addresses);

	new->ptr = 0;
	new->size = PC_RETURN_DEPTH;

	return new;
}

/* Frees memory assosiated with pc_t* instance
 */
void pc_del(pc_t* pc)
{
	N_ASSERT(pc, "pc_del\n");
	N_ASSERT(pc->stk, "pc_del\n");
// gotta actually handle this realquick
	free(pc);
}

void pc_addr_stk_del(pc_addr_stk* stk)
{
	N_ASSERT(stk, "pc_addr_stk_del\n");
// and this
}

void pc_push(pc_t* pc, bc_cont* bytecode)
{
	N_ASSERT(pc, "pc_push\n");
}

/* Updates currently reading line
 *
 * When called, pc_t->line will reflect pc_t->heap[pc_t->address]
 */
void pc_update(pc_t* pc)
{
	N_ASSERT(pc, "pc_update\n");
	
	pc->line = pc->heap[pc->address];
}

/* Increment program counter by +-addr
 */
void pc_inc(pc_t* pc, pc_addr addr)
{
	N_ASSERT(pc, "pc_inc\n");

	pc->address = pc->address + addr;
}

/* Branch to addr
 */
void pc_branch(pc_t* pc, pc_addr address)
{
	N_ASSERT(pc, "pc_branch\n");

	pc->address = address;
}

/* Return from branch
 */
void pc_return(pc_t* pc)
{
	N_ASSERT(pc, "pc_return\n");
}

/* For now, a simple function that returns true if the next instruction is not
 * NULL.
 */
int pc_safe(pc_t* pc)
{
	return 0;
}

