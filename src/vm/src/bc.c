#include <stdlib.h>
#include <stdio.h>

#include "bc.h"

#include "var.h"
#include "is.h"
#include "fh.h"
#include "helper.h"

/* Handles allocation for new `bc_cont` instances
 */
bc_cont* bc_cont_new(void)
{
	bc_cont *new = (bc_cont*)malloc(sizeof(bc_cont));
	M_ASSERT(new);

	new->args[0] = NULL;
	new->args[1] = NULL;
	new->args[2] = NULL;

	new->targ[0] = NULL;
	new->targ[1] = NULL;
	new->targ[2] = NULL;

	new->sarg[0] = 0;
	new->sarg[1] = 0;
	new->sarg[2] = 0;

	new->next = NULL;
	new->prev = NULL;

	return new;
}

/* Pushes new bc_cont to the chain.
 * bc_cont* - bytecode container
 *
 * -> bc_cont* - push new bytecode container on chain
 */
void bc_cont_push(bc_cont** head)
{
	(*head)->next = bc_cont_new();
	(*head)->next->prev = *head;
	*head = (*head)->next;
}

void bc_cont_del(bc_cont* root)
{
	if (root->next != NULL)
	{
		bc_cont_del(root->next);
	}

	if (root != NULL)
	{
		if (root->args[0] != NULL) free(root->args[0]);
		if (root->args[1] != NULL) free(root->args[1]);
		if (root->args[2] != NULL) free(root->args[2]);

		if (root->targ[0] != NULL) free(root->targ[0]);
		if (root->targ[1] != NULL) free(root->targ[1]);
		if (root->targ[2] != NULL) free(root->targ[2]);
	
		free(root);
	}
}

/* Given a file object, and an instance of `bc_cont` with proper metadata, this
 * function will read arguements into bc_cont.
 */
void get_args(FILE* f, bc_cont* ins)
{
	int num_args,
	    arg_types[3];

	unencode(ins->mdata, &num_args, arg_types);

	for (int x = 0; x < num_args; x++)
	{
		if (arg_types[x] == A_BYTE)
		{
			ins->args[x] = get_byte_arg(f, &ins->sarg[x]);
		} else
		if (arg_types[x] == A_WORD)
		{
			ins->args[x] = get_word_arg(f, &ins->sarg[x]);
		} else
		if (arg_types[x] == A_DYNC)
		{
			ins->args[x] = get_dync_arg(f, &ins->sarg[x]);
		}
	}
}
byte_t* get_byte_arg(FILE* f, int* size)
{
	*size = 1;
	return read_bytes(f, 1);
}
byte_t* get_word_arg(FILE* f, int* size)
{
	*size = 2;
	return read_bytes(f, 2);
}
byte_t* get_dync_arg(FILE* f, int* size)
{
	int n = 0;

	byte_t byte = read_byte(f);

	// This bit gets the length in bytes it needs to read into a buffer
	while (byte != 0)
	{
		n = (n << 8 | byte);
		byte = read_byte(f);
	}

	*size = n;

	return read_bytes(f, n);
}

/* Given an instruction, convert raw arguement data into typed data
 *  bc_cont* - bytecode container
 */
void process_args(bc_cont* ins)
{
	int num_args,
	    arg_types[3];

	unencode(ins->adata, &num_args, arg_types);

	for (int x = 0; x < num_args; x++)
	{
		if (arg_types[x] == BTOI)
		{
			arg_to_int(&ins->targ[x], ins->args[x]);
		} else
		if (arg_types[x] == WTOA)
		{
			arg_to_addr(&ins->targ[x], ins->args[x]);
		} else
		if (arg_types[x] == DTOL)
		{
			arg_to_arglist(&ins->targ[x], ins->sarg[x], ins->args[x]);
		} else
		if (arg_types[x] == DTOV)
		{
			arg_to_var(&ins->targ[x], ins->sarg[x], ins->args[x]);
		}
	}
}

void arg_to_int(void** ptr, byte_t* byte)
{
	*ptr = (bc_targ_int*)malloc(sizeof(bc_targ_int));
	M_ASSERT(*ptr);

	bc_targ_int* v = *ptr;

	v->i = (int)byte[0];
}

void arg_to_addr(void** ptr, byte_t* word)
{
	*ptr = (bc_targ_int*)malloc(sizeof(bc_targ_int));
	M_ASSERT(*ptr);

	bc_targ_int* v = *ptr;
	
	v->i = (int)(word[0] << 8 | word[1]);
}

void arg_to_arglist(void** ptr, int n, byte_t* bytes)
{
	*ptr = (bc_targ_list*)malloc(sizeof(bc_targ_list));
	M_ASSERT(*ptr);

//	bc_targ_list* v = *ptr;
}

void arg_to_var(void** ptr, int n, byte_t* bytes)
{
	*ptr = (bc_targ_var_cont*)malloc(sizeof(bc_targ_list));
	M_ASSERT(*ptr);

//	bc_targ_var_cont* v = *ptr;
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
		if (scanto < 0 && ptr->prev != NULL)
		{
			ptr = ptr->prev;
			scanto++;
		} else
		if (ptr->next == NULL || ptr->prev == NULL)
		{
			scanto = 0;
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
		process_args(ptr);

		ptr->real_addr = addr;

		bc_cont_push(&ptr);

		addr++;
	}

	fclose(f);

	return root;
}
