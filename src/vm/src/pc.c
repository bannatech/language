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

	pc->root = bc_read(fname);
	N_ASSERT(pc->root);

	pc->line = pc->root;

	pc->address = pc->root->real_addr;

	return pc;
}

void pc_del(pc_t* pc)
{
	N_ASSERT(pc);
	N_ASSERT(pc->root);
	bc_cont_del(pc->root);

	free(pc);
}

void pc_update(pc_t* pc)
{
	N_ASSERT(pc);

	pc->line = bc_scan(pc->line, pc->address - pc->line->real_addr);
}

void pc_inc(pc_t* pc, pc_addr addr)
{
	N_ASSERT(pc);

	pc->address = pc->address + addr;
}


void pc_branch(pc_t* pc, pc_addr addr)
{
	N_ASSERT(pc);

	pc->address = addr;
}
