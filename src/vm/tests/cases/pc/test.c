#include <stdlib.h>
#include <stdio.h>

#include "pc.h"
#include "fh.h"
#include "is.h"
#include "bc.h"

int main(int argc, char *argv[])
{
	init();

	pc_t* pc = pc_new("bytecode");

	while (pc->line->next != NULL)
	{
		pc_inc(pc, 1);

		printf("OP: %x\n", pc->line->op);

		pc_update(pc);
	}

	pc_del(pc);
	return 0;
}
