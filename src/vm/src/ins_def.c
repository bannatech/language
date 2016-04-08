#include <stdlib.h>
#include <stdio.h>

#include "ins_def.h"

#include "proc.h"
#include "rt.h"
#include "bc.h"
#include "stk.h"
#include "var.h"
#include "var_ops.h"
#include "pc.h"
#include "helper.h"

/* Initializes INS_DEF with pointers to each instructions function
 * Populates INS_DEF
 */
void init_ins_def( void )
{
	INS_DEF[0x00] = _ins_def_NULL;
	INS_DEF[0x01] = _ins_def_SYNC;
	INS_DEF[0x02] = _ins_def_PRINT;
	INS_DEF[0x0E] = _ins_def_ARGB;
	INS_DEF[0x0F] = _ins_def_LIBC;

	INS_DEF[0x10] = _ins_def_POP;
	INS_DEF[0x11] = _ins_def_ROT;
	INS_DEF[0x12] = _ins_def_DUP;
	INS_DEF[0x13] = _ins_def_ROT_THREE;

	INS_DEF[0x20] = _ins_def_DEC;
	INS_DEF[0x21] = _ins_def_LOV;
	INS_DEF[0x22] = _ins_def_STV;
	INS_DEF[0x23] = _ins_def_CTV;
	INS_DEF[0x24] = _ins_def_CTS;

	INS_DEF[0x30] = _ins_def_TYPEOF;
	INS_DEF[0x31] = _ins_def_CAST;

	INS_DEF[0x40] = _ins_def_ADD;
	INS_DEF[0x41] = _ins_def_SUB;
	INS_DEF[0x42] = _ins_def_MULT;
	INS_DEF[0x43] = _ins_def_DIV;
	INS_DEF[0x44] = _ins_def_POW;
	INS_DEF[0x45] = _ins_def_BRT;
	INS_DEF[0x46] = _ins_def_SIN;
	INS_DEF[0x47] = _ins_def_COS;
	INS_DEF[0x48] = _ins_def_TAN;
	INS_DEF[0x49] = _ins_def_ISIN;
	INS_DEF[0x4A] = _ins_def_ICOS;
	INS_DEF[0x4B] = _ins_def_ITAN;
	INS_DEF[0x4C] = _ins_def_MOD;
	INS_DEF[0x4D] = _ins_def_BOR;
	INS_DEF[0x4E] = _ins_def_BXOR;
	INS_DEF[0x4F] = _ins_def_BNAND;

	INS_DEF[0x50] = _ins_def_GTHAN;
	INS_DEF[0x51] = _ins_def_LTHAN;
	INS_DEF[0x51] = _ins_def_GTHAN_EQ;
	INS_DEF[0x52] = _ins_def_LTHAN_EQ;
	INS_DEF[0x53] = _ins_def_EQ;
	INS_DEF[0x54] = _ins_def_NOT;
	INS_DEF[0x55] = _ins_def_OR;
	INS_DEF[0x56] = _ins_def_AND;

	INS_DEF[0x60] = _ins_def_STARTL;
	INS_DEF[0x61] = _ins_def_CLOOP;
	INS_DEF[0x6E] = _ins_def_BREAK;
	INS_DEF[0x6F] = _ins_def_ENDL;

	INS_DEF[0x70] = _ins_def_GOTO;
	INS_DEF[0x71] = _ins_def_JUMPF;
	INS_DEF[0x73] = _ins_def_ELSE;
	INS_DEF[0x7E] = _ins_def_DONE;
	INS_DEF[0x7F] = _ins_def_CALL;

	INS_DEF[0x80] = _ins_def_PUSH;
	INS_DEF[0x81] = _ins_def_DEL;
	INS_DEF[0x82] = _ins_def_GET;
	INS_DEF[0x83] = _ins_def_GETP;
	INS_DEF[0x84] = _ins_def_CALLM;

	INS_DEF[0xF0] = _ins_def_RETURN;
	INS_DEF[0xF1] = _ins_def_NEW;
	INS_DEF[0xFE] = _ins_def_DECLASS;
	INS_DEF[0xFF] = _ins_def_DEFUN;
}

int ins_def_is_valid(bc_cont* line)
{
	int rv = 0;

	if(INS_DEF[line->op] != NULL)
	{
		rv = 1;
	}
	return rv;
}

void _ins_def_NULL     (rt_t* ctx, bc_cont* line)
{
	pc_inc(ctx->pc, 1);
}
void _ins_def_PRINT    (rt_t* ctx, bc_cont* line)
{
	var_cont* var = stk_pop(ctx->stack);

	if (var->type == G_STR)
	{
		char* str = var_data_get_G_STR(var);
		printf("%s\n", str);
	} else
	if (var->type == G_INT)
	{
		int val = var_data_get_G_INT(var);
		printf("%i\n", val);
	} else
	if (var->type == G_FLOAT)
	{
		double val = var_data_get_G_FLOAT(var);
		printf("%f\n", val);
	}

	pc_inc(ctx->pc, 1);
}
void _ins_def_SYNC     (rt_t* ctx, bc_cont* line)
{
	pc_inc(ctx->pc, 1);
}
void _ins_def_ARGB     (rt_t* ctx, bc_cont* line)
{
	var_cont* var = stk_at(ctx->stack, 0);

	stk_push(ctx->argstk, var);
	pc_inc(ctx->pc, 1);
}
void _ins_def_LIBC     (rt_t* ctx, bc_cont* line)
{
	pc_inc(ctx->pc, 1);
}

void _ins_def_POP      (rt_t* ctx, bc_cont* line)
{
	int n = var_data_get_G_INT(line->varg[0]);
	int i = 0;

	while (n > i)
	{
		i++;
		stk_pop(ctx->stack);
	}

	pc_inc(ctx->pc, 1);
}
void _ins_def_ROT      (rt_t* ctx, bc_cont* line)
{
	stk_rot_top(ctx->stack);

	pc_inc(ctx->pc, 1);
}
void _ins_def_DUP      (rt_t* ctx, bc_cont* line)
{
	var_cont* var = stk_at(ctx->stack, 0);
	var_cont* dup = var_data_cpy(var);
	stk_push(ctx->stack, dup);
	pc_inc(ctx->pc, 1);
}
void _ins_def_ROT_THREE(rt_t* ctx, bc_cont* line)
{
	stk_rot_three(ctx->stack);
	pc_inc(ctx->pc, 1);
}

void _ins_def_DEC      (rt_t* ctx, bc_cont* line)
{
	int scope = var_data_get_G_INT(line->varg[0]);
	int type  = var_data_get_G_INT(line->varg[1]);
	int name  = var_data_get_G_INT(line->varg[2]);

	proc_decvar(ctx, type, scope, name);

	pc_inc(ctx->pc, 1);
}
void _ins_def_LOV      (rt_t* ctx, bc_cont* line)
{
	int scope = var_data_get_G_INT(line->varg[0]);
	int name  = var_data_get_G_INT(line->varg[1]);

	var_cont* var;

	var = proc_getvar(ctx, scope, name);

	stk_push(ctx->stack, var);

	pc_inc(ctx->pc, 1);
}
void _ins_def_STV      (rt_t* ctx, bc_cont* line)
{
	int scope = var_data_get_G_INT(line->varg[0]);
	int name  = var_data_get_G_INT(line->varg[1]);

	var_cont* var = stk_pop(ctx->stack);

	proc_setvar(ctx, scope, name, var);

	pc_inc(ctx->pc, 1);
}
void _ins_def_CTV      (rt_t* ctx, bc_cont* line)
{
	int scope     = var_data_get_G_INT(line->varg[0]);
	int name      = var_data_get_G_INT(line->varg[1]);

	var_cont* new = var_data_cpy(line->varg[2]);

	proc_setvar(ctx, scope, name, new);

	pc_inc(ctx->pc, 1);
}
void _ins_def_CTS      (rt_t* ctx, bc_cont* line)
{
	var_cont* new = var_data_cpy(line->varg[0]);

	stk_push(ctx->stack, new);
	pc_inc(ctx->pc, 1);
}

void _ins_def_TYPEOF   (rt_t* ctx, bc_cont* line)
{
	var_cont* var = stk_at(ctx->stack, 0);
	var_cont* new = var_new(TYPE);

	var_data_type* data = var_data_alloc_TYPE(var->type);

	var_set(new, data, TYPE);

	stk_push(ctx->stack, new);

	pc_inc(ctx->pc, 1);
}
void _ins_def_CAST     (rt_t* ctx, bc_cont* line)
{
	pc_inc(ctx->pc, 1);
}

void _ins_def_ADD      (rt_t* ctx, bc_cont* line)
{
	var_cont* A = stk_pop(ctx->stack);
	var_cont* B = stk_pop(ctx->stack);

	var_cont* var = var_add(A, B);

	stk_push(ctx->stack, var);

	pc_inc(ctx->pc, 1);
}
void _ins_def_SUB      (rt_t* ctx, bc_cont* line)
{
	var_cont* A = stk_pop(ctx->stack);
	var_cont* B = stk_pop(ctx->stack);

	var_cont* var = var_sub(A, B);

	stk_push(ctx->stack, var);

	pc_inc(ctx->pc, 1);
}
void _ins_def_MULT     (rt_t* ctx, bc_cont* line)
{
	var_cont* A = stk_pop(ctx->stack);
	var_cont* B = stk_pop(ctx->stack);

	var_cont* var = var_mult(A, B);

	stk_push(ctx->stack, var);

	pc_inc(ctx->pc, 1);
}
void _ins_def_DIV      (rt_t* ctx, bc_cont* line)
{
	var_cont* A = stk_pop(ctx->stack);
	var_cont* B = stk_pop(ctx->stack);

	var_cont* var = var_mult(A, B);

	stk_push(ctx->stack, var);

	pc_inc(ctx->pc, 1);
}
void _ins_def_POW      (rt_t* ctx, bc_cont* line)
{
	pc_inc(ctx->pc, 1);
}
void _ins_def_BRT      (rt_t* ctx, bc_cont* line)
{
	pc_inc(ctx->pc, 1);
}
void _ins_def_SIN      (rt_t* ctx, bc_cont* line)
{
	pc_inc(ctx->pc, 1);
}
void _ins_def_COS      (rt_t* ctx, bc_cont* line)
{
	pc_inc(ctx->pc, 1);
}
void _ins_def_TAN      (rt_t* ctx, bc_cont* line)
{
	pc_inc(ctx->pc, 1);
}
void _ins_def_ISIN     (rt_t* ctx, bc_cont* line)
{
	pc_inc(ctx->pc, 1);
}
void _ins_def_ICOS     (rt_t* ctx, bc_cont* line)
{
	pc_inc(ctx->pc, 1);
}
void _ins_def_ITAN     (rt_t* ctx, bc_cont* line)
{
	pc_inc(ctx->pc, 1);
}
void _ins_def_MOD      (rt_t* ctx, bc_cont* line)
{
	pc_inc(ctx->pc, 1);
}
void _ins_def_BOR      (rt_t* ctx, bc_cont* line)
{
	pc_inc(ctx->pc, 1);
}
void _ins_def_BXOR     (rt_t* ctx, bc_cont* line)
{
	pc_inc(ctx->pc, 1);
}
void _ins_def_BNAND    (rt_t* ctx, bc_cont* line)
{
	pc_inc(ctx->pc, 1);
}

void _ins_def_GTHAN    (rt_t* ctx, bc_cont* line)
{
	var_cont* A = stk_pop(ctx->stack);
	var_cont* B = stk_pop(ctx->stack);

	var_cont* C = var_gthan(A, B);

	stk_push(ctx->stack, C);

	pc_inc(ctx->pc, 1);
}
void _ins_def_LTHAN    (rt_t* ctx, bc_cont* line)
{
	var_cont* A = stk_pop(ctx->stack);
	var_cont* B = stk_pop(ctx->stack);

	var_cont* C = var_lthan(A, B);

	stk_push(ctx->stack, C);

	pc_inc(ctx->pc, 1);
}
void _ins_def_GTHAN_EQ (rt_t* ctx, bc_cont* line)
{
	var_cont* A = stk_pop(ctx->stack);
	var_cont* B = stk_pop(ctx->stack);

	var_cont* C = (var_gthan(A, B) || var_eq(A, B));

	stk_push(ctx->stack, C);

	pc_inc(ctx->pc, 1);
}
void _ins_def_LTHAN_EQ (rt_t* ctx, bc_cont* line)
{
	var_cont* A = stk_pop(ctx->stack);
	var_cont* B = stk_pop(ctx->stack);

	var_cont* C = (var_lthan(A, B) || var_eq(A, B));

	stk_push(ctx->stack, C);

	pc_inc(ctx->pc, 1);
}
void _ins_def_EQ       (rt_t* ctx, bc_cont* line)
{
	var_cont* A = stk_pop(ctx->stack);
	var_cont* B = stk_pop(ctx->stack);

	var_cont* C = var_eq(A, B);

	stk_push(ctx->stack, C);

	pc_inc(ctx->pc, 1);
}
void _ins_def_NOT      (rt_t* ctx, bc_cont* line)
{
	pc_inc(ctx->pc, 1);
}
void _ins_def_OR       (rt_t* ctx, bc_cont* line)
{
	pc_inc(ctx->pc, 1);
}
void _ins_def_AND      (rt_t* ctx, bc_cont* line)
{
	pc_inc(ctx->pc, 1);
}

void _ins_def_STARTL   (rt_t* ctx, bc_cont* line)
{
	pc_branch(ctx->pc, ctx->pc->address);
	pc_inc(ctx->pc, 1);
}
void _ins_def_CLOOP    (rt_t* ctx, bc_cont* line)
{
	var_cont* var = stk_pop(ctx->stack);

	int value = var_data_get_G_INT(var);

	if (value < 1)
	{
		pc_return(ctx->pc);
		while (pc_safe(ctx->pc))
		{
			pc_update(ctx->pc);
			pc_inc(ctx->pc, 1);

			if (ctx->pc->line->op == 0x6F)
			{
				break;
			}
		}
	} else
	{
		pc_inc(ctx->pc, 1);
	}
}
void _ins_def_BREAK    (rt_t* ctx, bc_cont* line)
{
	pc_inc(ctx->pc, 1);
}
void _ins_def_ENDL     (rt_t* ctx, bc_cont* line)
{
	pc_return(ctx->pc);
}

void _ins_def_GOTO     (rt_t* ctx, bc_cont* line)
{
	pc_inc(ctx->pc, 1);
}
void _ins_def_JUMPF    (rt_t* ctx, bc_cont* line)
{
	pc_inc(ctx->pc, 1);
}
void _ins_def_IFDO     (rt_t* ctx, bc_cont* line)
{
	// Get the value off the stack
	var_cont* var = stk_pop(ctx->stack);
	int value = var_data_get_G_INT(var);

	// If the value is false, find an ELSE statement or DONE statement.
	if (value < 1)
	{
		while (pc_safe(ctx->pc))
		{
			pc_update(ctx->pc);
			pc_inc(ctx->pc, 1);
			// Is the instruction an ELSE statement?
			if (ctx->pc->line->op == 0x73)
			{
				// We're done here.
				break;
			} else
			// Is the instruction a DONE statement?
			if (ctx->pc->line->op == 0x7E)
			{
				// We're done here.
				break;
			}
		}
	}
}
void _ins_def_ELSE     (rt_t* ctx, bc_cont* line)
{
	pc_inc(ctx->pc, 1);
}
void _ins_def_DONE     (rt_t* ctx, bc_cont* line)
{
	pc_inc(ctx->pc, 1);
}
void _ins_def_CALL     (rt_t* ctx, bc_cont* line)
{
	int name = var_data_get_G_INT(line->varg[0]);

	// Get the function's variable container
	var_cont* var = proc_getvar(ctx, 1, name);
	var_data_func* func = var_data_get_FUNC(var);

	// Push a new namespace of specified size
	ns_push(ctx->vars, func->size);
	// Declare the return value
	ns_dec(ctx->vars, func->type, 0, 0);

	// Throw in the arguements on the arguement stack into the new namespace
	int offset = 1;
	int i;
	for (i = 0; i < func->paramlen; i++)
	{
		// Pop the arguement stack
		var_cont* arg = stk_pop(ctx->argstk);

		// Is the arguement of the right type?
		ASSERT(arg->type == func->param[i], "Invalid function call\n");

		// Declare the name in the new namespace and pass the arguements
		ns_dec(ctx->vars, arg->type, 0, i+offset);
		ns_set(ctx->vars, 0, i+offset, arg);
	}

	// Push new stack levels for the stack and the arguement stack
	stk_newlevel(&ctx->stack);
	stk_newlevel(&ctx->argstk);

	// Branch to functions body
	pc_branch(ctx->pc, func->loc);
}

void _ins_def_PUSH     (rt_t* ctx, bc_cont* line)
{
	pc_inc(ctx->pc, 1);
}
void _ins_def_DEL      (rt_t* ctx, bc_cont* line)
{
	pc_inc(ctx->pc, 1);
}
void _ins_def_GET      (rt_t* ctx, bc_cont* line)
{
	pc_inc(ctx->pc, 1);
}
void _ins_def_GETP     (rt_t* ctx, bc_cont* line)
{
	pc_inc(ctx->pc, 1);
}
void _ins_def_CALLM    (rt_t* ctx, bc_cont* line)
{
	pc_inc(ctx->pc, 1);
}

void _ins_def_RETURN   (rt_t* ctx, bc_cont* line)
{
	// Pop the namespace and get the return value
	var_cont* return_value = ns_pop(ctx->vars);

	// Pop a level in the stack and arguement stack
	stk_poplevel(&ctx->stack);
	stk_poplevel(&ctx->argstk);

	// Push the return value to the stack
	stk_push(ctx->stack, return_value);

	// Return to the callee
	pc_return(ctx->pc);

	// And increment the program counter
	pc_inc(ctx->pc, 1);
}
void _ins_def_NEW      (rt_t* ctx, bc_cont* line)
{
	pc_inc(ctx->pc, 1);
}
void _ins_def_DECLASS  (rt_t* ctx, bc_cont* line)
{
	pc_inc(ctx->pc, 1);
}
void _ins_def_DEFUN    (rt_t* ctx, bc_cont* line)
{
	int     name = var_data_get_G_INT(line->varg[0]);
	b_type  type = var_data_get_TYPE(line->varg[1]);
	b_type* args = var_data_get_PLIST(line->varg[2]);
	size_t  alen = line->sarg[2];

	// Create a new variable for the new function
	var_cont* func = var_new(FUNC);

	// Allocate the data.
	var_data_func* data = var_data_alloc_FUNC(type);

	// Set the location of the functions body
	data->loc = line->real_addr + 1;

	int nsize;
	/* Determine the namespace size by finding variable declarations in the functions body,
	   Along with determining the end of the function.
	 */
	for (nsize = 0; pc_safe(ctx->pc); pc_update(ctx->pc))
	{
		// Increment the program counter
		pc_inc(ctx->pc, 1);

		// Is this the end?
		if (ctx->pc->line->op == 0xF0)
		{
			break;
		} else
		// Are we declaring a variable?
		if (ctx->pc->line->op == 0x20)
		{
			// If so, increment the namespace size.
			nsize++;
		}
	}

	// Set all the values.
	data->end      = ctx->pc->line->real_addr; // This is the end!
	data->size     = nsize + alen + 1;         // How many names will this function have?
	data->type     = type;                     // Return type
	data->paramlen = alen;                     // Set the arguement length
	data->param    = args;                     // Set the parameter list

	// Throw the data in a variable container
	var_set(func, data, FUNC);

	// Declare a name
	proc_decvar(ctx, FUNC, 1, name);
	// Set the name's value to the function we just defined
	proc_setvar(ctx, 1, name, func);
}
