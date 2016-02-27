#include <stdlib.h>
#include <stdio.h>

#include "bc.h"
#include "is.h"
#include "fh.h"
#include "helper.h"

/* Handles allocation for new `bc_cont` instances
 */
bc_cont* bc_cont_new(void)
{
	bc_cont *new = (bc_cont*)malloc(sizeof(bc_cont));
	ASSERT(new != NULL, "Could not allocate memory\n");

	new->args[0] = NULL;
	new->args[1] = NULL;
	new->args[2] = NULL;

	return new;
}

/* Handles allocation for new `bc_cont` instances
 */
bc_cont* bc_cont_push(bc_cont* head)
{
	head->next = bc_cont_new();
	head->next->prev = head;
	return head->next;
}

/* Pushes new bc_cont to the chain.
 * bc_cont* - bytecode container
 *
 * -> bc_cont* - push new bytecode container on chain
 */
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

/* Deallocates all the things, assuming the arguement is the root.
 *  bc_cont* - bytecode container, root node (hopefully)
 */
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

/* Scan to +/- int in bytecode chain
 *  bc_cont* - bytecode container [0]
 *  int      - +/- up/down        [1]
 *
 * -> bc_cont* - Bytecode @param[0]'s location +/- @param[1]
 */
bc_cont* bc_scan(bc_cont* ptr, int scanto)
{
	while (scanto != 0)
	{
		if (scanto > 0 && ptr->next != NULL)
		{
			ptr = ptr->next;
			scanto--;
		} else
		if (scanto < 0 && ptr->next != NULL)
		{
			ptr = ptr->prev;
			scanto++;
		}
	}

	return ptr;
}

/* Initiates the first pass to take a raw binary file and translate it into a
 * basic datastructure
 */
bc_cont* bc_read(char* fname)
{
	FILE* f;
	byte_t byte;
	long fsize;
	
	f = fopen(fname, "rb");
	fsize = read_size(f);
	
	bc_cont *root = bc_cont_new();
	bc_cont *ptr  = root;
	bc_addr addr  = 0;

	/* Loop through file byte-by-byte */
	while (ftell(f)<fsize)
	{
		byte = read_byte(f);
		get_opcode(byte, ptr);
		get_args(f, ptr);

		ptr->real_addr = addr;

		ptr = bc_cont_push(ptr);

		addr++;
	}

	fclose(f);

	return root;
}
