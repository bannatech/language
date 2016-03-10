/* `INS_DEF` provides instruction definitons
 */

#ifndef INS_DEF_H
#define INS_DEF_H

#include <stdlib.h>
#include <stdio.h>

#include "proc.h"
#include "rt.h"
#include "bc.h"
#include "stk.h"
#include "var.h"
#include "var_ops.h"
#include "pc.h"
#include "helper.h"

// This array is populated by init_ins_def( void );
void (*INS_DEF[0xFF])(rt_t*, bc_cont*);

/* Initializes INS_DEF with pointers to each instructions function
 * Populates INS_DEF
 */
void init_ins_def( void );

/* Checks if instruction exists.
 *  byte_t - opcode
 */
int ins_def_is_valid(bc_cont*);

void _ins_def_NULL     (rt_t*, bc_cont*);
void _ins_def_SYNC     (rt_t*, bc_cont*);
void _ins_def_PRINT    (rt_t*, bc_cont*);
void _ins_def_ARGB     (rt_t*, bc_cont*);
void _ins_def_LIBC     (rt_t*, bc_cont*);

void _ins_def_POP      (rt_t*, bc_cont*);
void _ins_def_ROT      (rt_t*, bc_cont*);
void _ins_def_DUP      (rt_t*, bc_cont*);
void _ins_def_ROT_THREE(rt_t*, bc_cont*);

void _ins_def_DEC      (rt_t*, bc_cont*);
void _ins_def_LOV      (rt_t*, bc_cont*);
void _ins_def_STV      (rt_t*, bc_cont*);
void _ins_def_CTV      (rt_t*, bc_cont*);
void _ins_def_CTS      (rt_t*, bc_cont*);

void _ins_def_TYPEOF   (rt_t*, bc_cont*);
void _ins_def_CAST     (rt_t*, bc_cont*);

void _ins_def_ADD      (rt_t*, bc_cont*);
void _ins_def_SUB      (rt_t*, bc_cont*);
void _ins_def_MULT     (rt_t*, bc_cont*);
void _ins_def_DIV      (rt_t*, bc_cont*);
void _ins_def_POW      (rt_t*, bc_cont*);
void _ins_def_BRT      (rt_t*, bc_cont*);
void _ins_def_SIN      (rt_t*, bc_cont*);
void _ins_def_COS      (rt_t*, bc_cont*);
void _ins_def_TAN      (rt_t*, bc_cont*);
void _ins_def_ISIN     (rt_t*, bc_cont*);
void _ins_def_ICOS     (rt_t*, bc_cont*);
void _ins_def_ITAN     (rt_t*, bc_cont*);
void _ins_def_MOD      (rt_t*, bc_cont*);
void _ins_def_OR       (rt_t*, bc_cont*);
void _ins_def_XOR      (rt_t*, bc_cont*);
void _ins_def_NAND     (rt_t*, bc_cont*);

void _ins_def_GTHAN    (rt_t*, bc_cont*);
void _ins_def_LTHAN    (rt_t*, bc_cont*);
void _ins_def_EQ       (rt_t*, bc_cont*);
void _ins_def_NOT      (rt_t*, bc_cont*);

void _ins_def_STARTL   (rt_t*, bc_cont*);
void _ins_def_CLOOP    (rt_t*, bc_cont*);
void _ins_def_BREAK    (rt_t*, bc_cont*);
void _ins_def_ENDL     (rt_t*, bc_cont*);

void _ins_def_GOTO     (rt_t*, bc_cont*);
void _ins_def_JUMPF    (rt_t*, bc_cont*);
void _ins_def_IFDO     (rt_t*, bc_cont*);
void _ins_def_ELSE     (rt_t*, bc_cont*);
void _ins_def_DONE     (rt_t*, bc_cont*);
void _ins_def_CALL     (rt_t*, bc_cont*);

void _ins_def_PUSH     (rt_t*, bc_cont*);
void _ins_def_DEL      (rt_t*, bc_cont*);
void _ins_def_GET      (rt_t*, bc_cont*);
void _ins_def_GETP     (rt_t*, bc_cont*);
void _ins_def_CALLM    (rt_t*, bc_cont*);

void _ins_def_RETURN   (rt_t*, bc_cont*);
void _ins_def_NEW      (rt_t*, bc_cont*);
void _ins_def_DECLASS  (rt_t*, bc_cont*);
void _ins_def_DEFUN    (rt_t*, bc_cont*);

#endif //INS_DEF_H
