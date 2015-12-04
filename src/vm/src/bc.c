#include <stdio.h>
#include <stdlib.h>

#include "bc.h"
#include "is.h"

bc_cont* bc_cont_new(void)
{
	bc_cont *new = (bc_cont*)malloc(sizeof(bc_cont));
	if (new == NULL) {
		fprintf(stderr, "Cannot allocate memory\n");
		exit(1);
	}
	return new;
}

void bc_cont_del(bc_cont* root)
{
	if (root->next != NULL)
	{
		bc_cont_del(root->next);
	}
	free(root->args[0]);
	free(root->args[1]);
	free(root->args[2]);
	free(root);
}

void get_args(FILE** f, long* f_pos, bc_cont** ins)
{
	int num_args,
	    arg_types[3];

	get_mdata((*ins)->mdata, &num_args, arg_types);

	for (int x = 0; x <= num_args; x++)
	{
		unsigned char arg;
		if (arg_types[x] == A_BYTE)
		{
			arg = get_byte_arg(f, f_pos);
		} else
		if (arg_types[x] == A_WORD)
		{
			arg = get_word_arg(f, f_pos);
		} else
		if (arg_types[x] == A_DYNC)
		{
			arg = get_dync_arg(f, f_pos);
		}
	}
}

unsigned char get_byte_arg(FILE** f, long* f_pos)
{
	unsigned char arg;
	return arg;
}

unsigned char get_word_arg(FILE** f, long* f_pos)
{
	unsigned char arg;
	return arg;
}

unsigned char get_dync_arg(FILE** f, long* f_pos)
{
	unsigned char arg;
	return arg;
}

long read_size(FILE** f, char* fname)
{
	*f = fopen(fname, "rb");
	fseek(*f, 0, SEEK_END);

	long fsize = 0;
	fsize = ftell(*f);
	rewind(*f);

	return fsize;
}

bc_cont* bc_read(char* fname)
{
	/* initialize datastructures for instructionstuffs,
	   begin to read file byte-by-byte */
	FILE* f;
	char byte;
	long f_pos = 0;
	long fsize = read_size(&f, fname);
	
	bc_cont *root = bc_cont_new();
	bc_cont **ptr = &root;

	/* Loop through file byte-by-byte */
	while (f_pos<fsize)
	{
		byte = fgetc(f);
		f_pos++;

		get_opcode(byte, ptr);
		get_args(&f, &f_pos, ptr);

		(*ptr)->next = bc_cont_new();
		ptr = &((*ptr)->next);
	}

	fclose(f);

	return root;
}
