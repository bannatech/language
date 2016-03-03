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
		if (arg_types[i] == 1)
		{
			printf("%x", op->args[i][0]);
		} else
		if (arg_types[i] == 2)
		{
			printf("%x %x", op->args[i][1], op->args[i][0]);
		} else
		if (arg_types[i] == 3)
		{
			for (int x = 0; x < op->sarg[i]; x++)
				printf("%x ", op->args[i][x]);
		}
		printf(", ");
	}

	printf("\n");
}

int main(int argc, char** argv)
{
	init_mdata();
	init_adata();

	// start testing
	bc_cont* bc = bc_read("bytecode");
	bc_cont* ptr;
	
	for (ptr = bc; ptr->next != NULL; ptr = ptr->next)
	{
		print_op(ptr);
	}

	bc_cont_del(bc);
	// end testing
	return 0;
}
