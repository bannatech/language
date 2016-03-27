#include <stdlib.h>
#include <stdio.h>

#include "bc.h"

#include "fh.h"
#include "var.h"
#include "helper.h"
#include "is.h"

/* Handles allocation for new `bc_cont` instances
 */
bc_cont* bc_cont_new(void)
{
	bc_cont *new = (bc_cont*)malloc(sizeof(bc_cont));
	M_ASSERT(new);

	new->args[0] = NULL;
	new->args[1] = NULL;
	new->args[2] = NULL;

	new->varg[0] = NULL;
	new->varg[1] = NULL;
	new->varg[2] = NULL;

	new->sarg[0] = 0;
	new->sarg[1] = 0;
	new->sarg[2] = 0;

	return new;
}

void bc_cont_del(bc_cont* ins)
{
	if (ins != NULL)
	{
		if (ins->args[0] != NULL) free(ins->args[0]);
		if (ins->args[1] != NULL) free(ins->args[1]);
		if (ins->args[2] != NULL) free(ins->args[2]);

		if (ins->varg[0] != NULL) var_del(ins->varg[0]);
		if (ins->varg[1] != NULL) var_del(ins->varg[1]);
		if (ins->varg[2] != NULL) var_del(ins->varg[2]);
	
		free(ins);
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
		if (arg_types[x] == A_NAME)
		{
			ins->args[x] = get_name_arg(f, &ins->sarg[x]);
		} else
		if (arg_types[x] == A_ADDR)
		{
			ins->args[x] = get_addr_arg(f, &ins->sarg[x]);
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
byte_t* get_name_arg(FILE* f, int* size)
{
	*size = NAMELEN;
	return read_bytes(f, NAMELEN);
}
byte_t* get_addr_arg(FILE* f, int* size)
{
	*size = ADDRLEN;
	return read_bytes(f, ADDRLEN);
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

	int x;
	for (x = 0; x < num_args; x++)
	{
		if (arg_types[x] == BTOI)
		{
			ins->varg[x] = raw_to_int(ins->sarg[x], 0, ins->args[x]);
			ins->varg[x]->ownership = 0;
		} else
		if (arg_types[x] == BTOT)
		{
			ins->varg[x] = byte_to_type(ins->args[x][0]);
			ins->varg[x]->ownership = 0;
		} else
		if (arg_types[x] == DTOL)
		{
			ins->varg[x] = raw_to_plist(ins->sarg[x], ins->args[x]);
			ins->varg[x]->ownership = 0;
		} else
		if (arg_types[x] == DTOV)
		{
			ins->varg[x] = raw_to_var(ins->sarg[x], ins->args[x]);
			ins->varg[x]->ownership = 0;
		}
	}
}

/* Reads program into bc_cont instances
 *  FILE*    - File descriptor
 *  bc_addr* - pointer to size variable
 */
bc_cont** bc_read(FILE* f, bc_addr* len)
{
	N_ASSERT(f, "bc_read\n");

	long fsize = read_size(f);

	bc_addr addr = 0;
	bc_cont* ptr;
	byte_t byte;

	bc_cont** heap = (bc_cont**)malloc(sizeof(bc_cont*)*fsize);
	N_ASSERT(heap, "bc_read\n");

	/* Loop through file byte-by-byte */
	while (ftell(f) < fsize)
	{
		ptr = bc_cont_new();

		byte = read_byte(f);

		get_opcode(byte, ptr);

		get_args(f, ptr);

		process_args(ptr);

		ptr->real_addr = addr;

		heap[addr] = ptr;

		addr++;
	}

	*len = addr;
	return heap;
}

/* Reads program into bc_t instance
 *  char* - filename
 */
bc_t* bc_init(char* fname)
{
	N_ASSERT(fname, "bc_init\n");

	FILE* f;

	bc_t* program;
	
	f = fopen(fname, "rb");

	program = (bc_t*)malloc(sizeof(bc_t));
	N_ASSERT(program, "bc_read\n");

	program->heap = bc_read(f, &program->size);

	fclose(f);

	return program;
}

/* Deletes instance of bc_t*
 */
void bc_del(bc_t* program)
{
	N_ASSERT(program, "bc_del\n");

	int i;
	for (i=0; i < program->size; i++)
	{
		if (program->heap[i] != NULL)
			bc_cont_del(program->heap[i]);
	}

	free(program->heap);

	free(program);
}
