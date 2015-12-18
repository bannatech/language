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
	bc_cont* ptr;
	
	for (ptr = bc; ptr->next != NULL; ptr = ptr->next)
	{
		if (ptr->op == 1)
		{
			printf("%x:\n", ptr->op);
		}
		if (ptr->op == 2)
		{
			printf("%x: %x\n", ptr->op, ptr->args[0][0]);
		}
		if (ptr->op == 3)
		{
			printf("%x: %x, %x %x\n",
			       ptr->op, ptr->args[0][0], ptr->args[1][0], ptr->args[1][1]);
		}
		if (ptr->op == 4)
		{
			printf("%x: ", ptr->op);
			int len = sizeof(ptr->args[0]);
			for (int i = 0; i < len; i++) printf("%x ", ptr->args[0][i]);
			printf("\n");
		}
	}

	bc_cont_del(bc);
	// end testing
	return 0;
}
