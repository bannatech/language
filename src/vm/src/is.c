#include <stdlib.h>

#include "is.h"

#include "fh.h"
#include "bc.h"

#include "ins_mdata.h"

/* Takes an opcode, fills metadata about that opcode (given that it exists) in
 * the `bc_cont` structure
 *  byte_t   - opcode
 *  bc_cont* - Bytecode instruction
 */
void get_opcode_mdata(byte_t byte, bc_cont* ins)
{
	ins->op    = byte;
	ins->mdata = INS_MDATA[byte];
	ins->adata = INS_ADATA[byte];
}

/* Fills in metadata in @param byte_t.
 * byte_t - un-expanded metadata
 * int*   - is number of params          [0]
 * int*   - int[3] detailing param types [1]
 *
 * For example, given a byte 11011011, it would break down into the following:
 * @param[1] = 3,
 * @param[2] = { 01, 10, 11 }
 */
void unencode(byte_t byte, int* n, int* at)
{
	*n    = (byte & (3 << 6)) >> 6;
	at[0] = (byte & (3 << 4)) >> 4;
	at[1] = (byte & (3 << 2)) >> 2;
	at[2] = (byte &  3)           ;
}

/* Sets up the datastructure to quickly queue for data.
 */
void init_mdata(void)
{
	INS_MDATA_DEF();
}

void init_adata(void)
{
	INS_ADATA_DEF();
}
