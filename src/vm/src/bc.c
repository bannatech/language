#include <stdio.h>
#include <stdlib.h>

#include "bc.h"
#include "is.h"
#include "fh.h"
#include "helper.h"

bc_cont* bc_cont_new(void)
{
	bc_cont *new = (bc_cont*)malloc(sizeof(bc_cont));
	ASSERT(new != NULL, "Could not allocate memory\n");

	new->args[0] = NULL;
	new->args[1] = NULL;
	new->args[2] = NULL;

	return new;
}

bc_cont* bc_cont_push(bc_cont* head)
{
	head->next = bc_cont_new();
	return head->next;
}

void bc_cont_del(bc_cont* root)
{
	if (root->next != NULL)
	{
		bc_cont_del(root->next);
	}

	if (root->args[0] != NULL) free(root->args[0]);
	if (root->args[1] != NULL) free(root->args[1]);
	if (root->args[2] != NULL) free(root->args[2]);

	free(root);
}

void get_args(FILE* f, bc_cont* ins)
{
	int num_args,
	    arg_types[3];

	get_mdata(ins->mdata, &num_args, arg_types);

	for (int x = 0; x < num_args; x++)
	{
		if (arg_types[x] == A_BYTE)
		{
			ins->args[x] = get_byte_arg(f);
		} else
		if (arg_types[x] == A_WORD)
		{
			ins->args[x] = get_word_arg(f);
		} else
		if (arg_types[x] == A_DYNC)
		{
			ins->args[x] = get_dync_arg(f);
		}
	}
}

byte_t* get_byte_arg(FILE* f)
{
	return read_bytes(f, 1);
}

byte_t* get_word_arg(FILE* f)
{
	return read_bytes(f, 2);
}

byte_t* get_dync_arg(FILE* f)
{
	return read_until_null(f);
}

bc_cont* bc_read(char* fname)
{
	FILE* f;
	byte_t byte;
	long fsize;
	
	f = fopen(fname, "rb");
	fsize = read_size(f);
	
	bc_cont *root = bc_cont_new();
	bc_cont *ptr = root;

	/* Loop through file byte-by-byte */
	while (ftell(f)<fsize)
	{
		byte = read_byte(f);
		get_opcode(byte, ptr);
		get_args(f, ptr);

		ptr = bc_cont_push(ptr);
	}

	fclose(f);
	return root;
}
