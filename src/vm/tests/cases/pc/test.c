#include <stdlib.h>
#include <stdio.h>

#include "pc.h"
#include "fh.h"
#include "is.h"
#include "bc.h"

int main(int argc, char *argv[])
{
	init_mdata();
	init_adata();

	printf("Loading file 'bytecode'\n");
	pc_t* pc = pc_new("bytecode");

	while (pc_safe(pc))
	{
		printf("ADDR: %lx, OP: %x\n", pc->address, pc->line->op);
		pc_inc(pc, 1);
		pc_update(pc);
	}
	pc_inc(pc, -1);
	pc_branch(pc, 1);
	pc_update(pc);

	while (pc_safe(pc))
	{
		printf("ADDR: %lx, OP: %x\n", pc->address, pc->line->op);
		pc_inc(pc, 1);
		pc_update(pc);
	}

	pc_return(pc);
	pc_update(pc);
	printf("ADDR: %lx, OP: %x\n", pc->address, pc->line->op);

	pc_del(pc);
	return 0;
}
