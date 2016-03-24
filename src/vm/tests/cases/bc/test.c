#include <stdio.h>

#include "fh.h"
#include "is.h"
#include "ins_mdata.h"
#include "ins_def.h"
#include "var.h"
#include "bc.h"

void print_op(bc_cont* op)
{
	int num_args,
	    arg_types[3];

	unencode(op->mdata, &num_args, arg_types);

	printf("%x: ", op->op);
	for (int i = 0; i < num_args && num_args != 0; i++)
	{
		if (arg_types[i] == A_BYTE)
		{
			printf("%x, ", op->args[i][0]);
		} else
		if (arg_types[i] == A_NAME)
		{
			printf("%x %x, ", op->args[i][1], op->args[i][0]);
		} else
		if (arg_types[i] == A_DYNC)
		{
			for (int x = 0; x < op->sarg[i]; x++)
				printf("%x ", op->args[i][x]);
		}
	}

	printf("\n");
}

int main(int argc, char** argv)
{
	init_mdata();
	init_adata();

	bc_t* bc = bc_init("bytecode");
	
	int i;
	for (i = 0; i < bc->size; i++)
	{
		print_op(bc->heap[i]);
	}

	bc_del(bc);
	return 0;
}
