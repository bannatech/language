#include <stdlib.h>
#include <stdio.h>

#include "pc.h"

#include "bc.h"
#include "is.h"
#include "fh.h"
#include "helper.h"

pc_t* pc_new(char* fname)
{
	N_ASSERT(fname);

	pc_t* pc = (pc_t*)malloc(sizeof(pc_t));
	M_ASSERT(pc);

	pc->stk = pc_stk_new();

	pc->root = bc_read(fname);

	pc->line = pc->root;

	pc->stk->address = pc->root->real_addr;

	return pc;
}

pc_stk* pc_stk_new()
{
	pc_stk* new = (pc_stk*)malloc(sizeof(pc_stk));
	M_ASSERT(new);

	new->next = NULL;

	return new;
}

void pc_del(pc_t* pc)
{
	N_ASSERT(pc);
	N_ASSERT(pc->stk);
	N_ASSERT(pc->root);

	bc_cont_del(pc->root);

	pc_stk_del(pc->stk);

	free(pc);
}

void pc_stk_del(pc_stk* stk)
{
	N_ASSERT(stk);

	if (stk->next != NULL)
	{
		pc_stk_del(stk->next);
	}

	free(stk);
}

void pc_update(pc_t* pc)
{
	N_ASSERT(pc);
	pc->line = bc_scan(pc->line, (pc->stk->address - pc->line->real_addr) );
}

void pc_inc(pc_t* pc, pc_addr addr)
{
	N_ASSERT(pc);

	pc->stk->address = pc->stk->address + addr;
}

void pc_branch(pc_t* pc, pc_addr addr)
{
	N_ASSERT(pc);

	pc_stk* new = pc_stk_new();

	new->next = pc->stk;

	pc->stk = new;
}

void pc_return(pc_t* pc)
{
	N_ASSERT(pc);

	pc_stk* tmp = pc->stk;
	pc->stk = pc->stk->next;
	free(tmp);
}
