#include <stdlib.h>

#include "is.h"
#include "bc.h"
#include "fh.h"

void get_opcode(byte_t byte, bc_cont** ins)
{
	(*ins)->op    = byte;
	(*ins)->mdata = INS_MDATA[byte];
}

void get_mdata(byte_t byte, int* n, int* at)
{
	*n    = (byte & (3 << 6)) >> 6;
	at[0] = (byte & (3 << 4)) >> 4;
	at[1] = (byte & (3 << 2)) >> 2;
	at[2] = (byte &  3)           ;
}

void init(void)
{
	init_mdata();
}

void init_mdata(void)
{
	#include "is_mdata"
}
