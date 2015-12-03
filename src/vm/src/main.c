#include <stdio.h>

#include "bc.h"

int main(int argc, char** argv)
{
	if (argc < 2) return -1;
	// start testing
	bc_cont* bc = bc_read(argv[1]);

	bc_cont_del(bc);
	// end testing
	return 0;
}
