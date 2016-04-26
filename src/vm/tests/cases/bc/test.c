#include <stdio.h>

#include "fh.h"
#include "is.h"
#include "ins_mdata.h"
#include "ins_def.h"
#include "var.h"
#include "bc.h"

int main(int argc, char** argv)
{
	init_mdata();
	init_adata();

	bc_t* bc = bc_init("bytecode");
	
	int i;
	for (i = 0; i < bc->size; i++)
	{
		bc_print_op(bc->heap[i]);
		printf("\n");
	}

	bc_del(bc);
	return 0;
}
