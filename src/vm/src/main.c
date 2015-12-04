#include <stdio.h>

#include "is.h"
#include "bc.h"

int main(int argc, char** argv)
{
	if (argc < 2) return -1;
	init();

	// start testing
	bc_cont* bc = bc_read(argv[1]);
	bc_cont** ptr;

	for (ptr = &bc; (*ptr)->next != NULL; ptr = &((*ptr)->next))
	{
		printf("%x, %x\n", (*ptr)->op, (*ptr)->mdata);
	}

	bc_cont_del(bc);
	// end testing
	return 0;
}
