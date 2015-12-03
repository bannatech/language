#include <stdlib.h>

#include "is.h"
#include "bc.h"

void get_opcode(char byte, bc_cont** ins)
{
	(*ins)->op    = byte;
	//(*ins)->mdata = INS_ARGS[byte];
}
