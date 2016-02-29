/* `ins_adata.h` provides per-opcode arguement type data.
 * Provides subroutines for individual opcodes
 */

#ifndef INS_MDATA_H
#define INS_MDATA_H

#include <stdlib.h>
#include <stdio.h>

#include "bc.h"
#include "is.h"
#include "var.h"
#include "helper.h"

void init_adata( void );

/* TODO: figure out how to deserialize the following:
 *
 *  Byte to integer
 *  Word to address type
 *  Dynamic length arguement to arguement type list
 *  Dynamic length arguement to typed data
 */

#endif //INS_MDATA_H
