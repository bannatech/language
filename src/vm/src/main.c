#include <stdio.h>

#include "fh.h"
#include "is.h"
#include "bc.h"

int main(int argc, char** argv)
{
	if (argc < 2) return -1;
	init();

	// start testing
	bc_cont* bc = bc_read(argv[1]);
	bc_cont** ptr;
	bc_cont* thing;

	for (ptr = &bc; (*ptr)->next != NULL; ptr = &((*ptr)->next))
	{
		thing = *ptr;
		if (thing->op == 2)
		{
			printf("%x\n", thing->args[0][0]);
		}
		if (thing->op == 3)
		{
			printf("%x, %x %x\n", thing->args[0][0], thing->args[1][0], thing->args[1][1]);
		}
		if (thing->op == 4)
		{
			int len = sizeof(thing->args[0]);
			for (int i = 0; i < len; i++) printf("%x ", thing->args[0][i]);
			printf("\n");
		}
	}

	bc_cont_del(bc);
	// end testing
	return 0;
}
