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
#include "pc.h"
#include "helper.h"

// This array is populated by init_ins_def( void );
void INS_DEF[0xFF];

/* Initializes INS_DEF with pointers to each instructions function
 * Populates INS_DEF
 */
void init_ins_def( void );

void _ins_def_NULL     (rt_t*, byte_t*);
void _ins_def_SYNC     (rt_t*, byte_t*);
void _ins_def_ARGB     (rt_t*, byte_t*);
void _ins_def_LIBC     (rt_t*, byte_t*);

void _ins_def_POP      (rt_t*, byte_t*);
void _ins_def_ROT      (rt_t*, byte_t*);
void _ins_def_DUP      (rt_t*, byte_t*);
void _ins_def_ROT_THREE(rt_t*, byte_t*);

void _ins_def_DEC      (rt_t*, byte_t*);
void _ins_def_LOV      (rt_t*, byte_t*);
void _ins_def_STV      (rt_t*, byte_t*);
void _ins_def_LOC      (rt_t*, byte_t*);
void _ins_def_CTS      (rt_t*, byte_t*);

void _ins_def_TYPEOF   (rt_t*, byte_t*);
void _ins_def_CAST     (rt_t*, byte_t*);

void _ins_def_ADD      (rt_t*, byte_t*);
void _ins_def_SUB      (rt_t*, byte_t*);
void _ins_def_MULT     (rt_t*, byte_t*);
void _ins_def_DIV      (rt_t*, byte_t*);
void _ins_def_POW      (rt_t*, byte_t*);
void _ins_def_BRT      (rt_t*, byte_t*);
void _ins_def_SIN      (rt_t*, byte_t*);
void _ins_def_COS      (rt_t*, byte_t*);
void _ins_def_TAN      (rt_t*, byte_t*);
void _ins_def_ISIN     (rt_t*, byte_t*);
void _ins_def_ICOS     (rt_t*, byte_t*);
void _ins_def_ITAN     (rt_t*, byte_t*);
void _ins_def_MOD      (rt_t*, byte_t*);
void _ins_def_OR       (rt_t*, byte_t*);
void _ins_def_XOR      (rt_t*, byte_t*);
void _ins_def_NAND     (rt_t*, byte_t*);

void _ins_def_GTHAN    (rt_t*, byte_t*);
void _ins_def_LTHAN    (rt_t*, byte_t*);
void _ins_def_EQ       (rt_t*, byte_t*);
void _ins_def_NOT      (rt_t*, byte_t*);

void _ins_def_STARTL   (rt_t*, byte_t*);
void _ins_def_CLOOP    (rt_t*, byte_t*);
void _ins_def_BREAK    (rt_t*, byte_t*);
void _ins_def_DONE     (rt_t*, byte_t*);

void _ins_def_GOTO     (rt_t*, byte_t*);
void _ins_def_JUMPF    (rt_t*, byte_t*);
void _ins_def_CALL     (rt_t*, byte_t*);

void _ins_def_PUSH     (rt_t*, byte_t*);
void _ins_def_DEL      (rt_t*, byte_t*);
void _ins_def_GET      (rt_t*, byte_t*);
void _ins_def_GETP     (rt_t*, byte_t*);
void _ins_def_CALLM    (rt_t*, byte_t*);

void _ins_def_RETURN   (rt_t*, byte_t*);
void _ins_def_NEW      (rt_t*, byte_t*);
void _ins_def_LSIZE    (rt_t*, byte_t*);
void _ins_def_DECLASS  (rt_t*, byte_t*);
void _ins_def_DEFUN    (rt_t*, byte_t*);

#endif //INS_DEF_H
