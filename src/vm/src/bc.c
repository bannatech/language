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
	free(root);
}

void get_args(FILE** f, long* i, bc_cont** ins)
{
	
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
	long i = 0;
	long fsize = read_size(&f, fname);
	
	bc_cont *root = bc_cont_new();
	bc_cont **ptr = &root;

	/* Loop through file byte-by-byte */
	while (i<fsize)
	{
		byte = fgetc(f);
		i++;
		get_opcode(byte, ptr);
		get_args(&f, &i, ptr);
		// Set `ptr` to next element
		(*ptr)->next = bc_cont_new();
		ptr = &((*ptr)->next);
	}

	// START TESTING CODE
	for (ptr = &root; (*ptr)->next != NULL; ptr = &((*ptr)->next))
	{
		printf("%x\n", (*ptr)->op);
	}
	// END TESTING CODE
	fclose(f);

	return root;
}
