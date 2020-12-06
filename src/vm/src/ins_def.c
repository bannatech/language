#include <stdlib.h>
#include <stdio.h>

#include "ins_def.h"

#include "proc.h"
#include "rt.h"
#include "bc.h"
#include "stk.h"
#include "object.h"
#include "var.h"
#include "var_ops.h"
#include "pc.h"
#include "helper.h"

/* Initializes INS_DEF with pointers to each instructions function
 * Populates INS_DEF
 */
void init_ins_def( void )
{
	INS_DEC(0x00, _ins_def_NULL, "NULL");
	INS_DEC(0x01, _ins_def_SYNC, "SYNC");

	INS_DEC(0x02, _ins_def_PRINT, "PRINT");
	INS_DEC(0x03, _ins_def_DEBUG, "DEBUG");
	INS_DEC(0x0E, _ins_def_ARGB, "ARGB");
	INS_DEC(0x0F, _ins_def_LIBC, "LIBC");

	INS_DEC(0x10, _ins_def_POP, "POP");
	INS_DEC(0x11, _ins_def_ROT, "ROT");
	INS_DEC(0x12, _ins_def_DUP, "DUP");
	INS_DEC(0x13, _ins_def_ROT_THREE, "ROT_THREE");

	INS_DEC(0x20, _ins_def_DEC, "DEC");
	INS_DEC(0x21, _ins_def_LOV, "LOV");
	INS_DEC(0x22, _ins_def_STV, "STV");
	INS_DEC(0x23, _ins_def_CTV, "CTV");
	INS_DEC(0x24, _ins_def_CTS, "CTS");

	INS_DEC(0x30, _ins_def_TYPEOF, "TYPEOF");
	INS_DEC(0x31, _ins_def_CAST, "CAST");

	INS_DEC(0x40, _ins_def_ADD, "ADD");
	INS_DEC(0x41, _ins_def_SUB, "SUB");
	INS_DEC(0x42, _ins_def_MULT, "MULT");
	INS_DEC(0x43, _ins_def_DIV, "DIV");
	INS_DEC(0x44, _ins_def_POW, "POW");
	INS_DEC(0x45, _ins_def_BRT, "BRT");
	INS_DEC(0x46, _ins_def_SIN, "SIN");
	INS_DEC(0x47, _ins_def_COS, "COS");
	INS_DEC(0x48, _ins_def_TAN, "TAN");
	INS_DEC(0x49, _ins_def_ISIN, "ISIN");
	INS_DEC(0x4A, _ins_def_ICOS, "ICOS");
	INS_DEC(0x4B, _ins_def_ITAN, "ITAN");
	INS_DEC(0x4C, _ins_def_MOD, "MOD");
	INS_DEC(0x4D, _ins_def_BOR, "BOR");
	INS_DEC(0x4E, _ins_def_BXOR, "BXOR");
	INS_DEC(0x4F, _ins_def_BNAND, "BNAND");

	INS_DEC(0x50, _ins_def_GTHAN, "GTHAN");
	INS_DEC(0x51, _ins_def_LTHAN, "LTHAN");
	INS_DEC(0x52, _ins_def_GTHAN_EQ, "GTHAN_EQ");
	INS_DEC(0x53, _ins_def_LTHAN_EQ, "LTHAN_EQ");
	INS_DEC(0x54, _ins_def_EQ, "EQ");
	INS_DEC(0x55, _ins_def_NEQ, "NEQ");
	INS_DEC(0x56, _ins_def_NOT, "NOT");
	INS_DEC(0x57, _ins_def_OR, "OR");
	INS_DEC(0x58, _ins_def_AND, "AND");

	INS_DEC(0x60, _ins_def_STARTL, "STARTL");
	INS_DEC(0x61, _ins_def_CLOOP, "CLOOP");
	INS_DEC(0x6E, _ins_def_BREAK, "BREAK");
	INS_DEC(0x6F, _ins_def_ENDL, "ENDL");

	INS_DEC(0x70, _ins_def_GOTO, "GOTO");
	INS_DEC(0x71, _ins_def_JUMPF, "JUMPF");
	INS_DEC(0x72, _ins_def_IFDO, "IFDO");
	INS_DEC(0x73, _ins_def_ELSE, "ELSE");
	INS_DEC(0x7E, _ins_def_DONE, "DONE");
	INS_DEC(0x7F, _ins_def_CALL, "CALL");

	INS_DEC(0x80, _ins_def_GETN, "GETN");
	INS_DEC(0x81, _ins_def_SETN, "SETN");
	INS_DEC(0x82, _ins_def_CALLM, "CALLM");
	INS_DEC(0x83, _ins_def_INDEXO, "INDEXO");
	INS_DEC(0x84, _ins_def_MODO, "MODO");

	INS_DEC(0xF0, _ins_def_RETURN, "RETURN");
	INS_DEC(0xF1, _ins_def_NEW, "NEW");
	INS_DEC(0xF2, _ins_def_ENDCLASS, "ENDCLASS");
	INS_DEC(0xFE, _ins_def_DECLASS, "DECLASS");
	INS_DEC(0xFF, _ins_def_DEFUN, "DEFUN");
}

int ins_def_is_valid(bc_cont* line)
{
	int rv = 0;

	if (INS_DEF[line->op] != NULL)
	{
		rv = 1;
	}
	return rv;
}

inline void run_ins(rt_t* ctx, bc_cont* line)
{
	INS_DEF[line->op](ctx, line);
}

void _ins_def_NULL     (rt_t* ctx, bc_cont* line)
{
	pc_inc(ctx->pc, 1);
}
void _ins_def_SYNC     (rt_t* ctx, bc_cont* line)
{
	pc_inc(ctx->pc, 1);
}
void _ins_def_PRINT    (rt_t* ctx, bc_cont* line)
{
	var_cont* var = stk_pop(ctx->stack);

	var_pprint(var);

	pc_inc(ctx->pc, 1);
}
void _ins_def_DEBUG    (rt_t* ctx, bc_cont* line)
{
	ctx->db = 0 ? ctx->db : 1;
	pc_inc(ctx->pc, 1);
}
void _ins_def_ARGB     (rt_t* ctx, bc_cont* line)
{
	var_cont* var = stk_pop(ctx->stack);

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
	b_type type  = var_data_get_TYPE(line->varg[1]);
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
	var_cont* ovr = proc_getvar(ctx, scope, name);
	var_cont* set = var_data_cpy(var);
	set->ownership = ovr->ownership;

	proc_setvar(ctx, scope, name, set);

	pc_inc(ctx->pc, 1);
}
void _ins_def_CTV      (rt_t* ctx, bc_cont* line)
{
	int name = var_data_get_G_INT(line->varg[0]);
	
	int scope = var_data_get_G_INT(line->varg[1]);

	var_cont* new = var_data_cpy(line->varg[2]);

	proc_setvar(ctx, scope, name, new);

	pc_inc(ctx->pc, 1);
}
void _ins_def_CTS      (rt_t* ctx, bc_cont* line)
{
	//var_cont* new = var_data_cpy(line->varg[0]);

	stk_push(ctx->stack, line->varg[0]);

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

	var_cont* var = var_div(A, B);

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

	var_cont* C = var_gthan_eq(A, B);

	stk_push(ctx->stack, C);

	pc_inc(ctx->pc, 1);
}
void _ins_def_LTHAN_EQ (rt_t* ctx, bc_cont* line)
{
	var_cont* A = stk_pop(ctx->stack);
	var_cont* B = stk_pop(ctx->stack);

	var_cont* C = var_gthan_eq(A, B);

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
void _ins_def_NEQ       (rt_t* ctx, bc_cont* line)
{
	var_cont* A = stk_pop(ctx->stack);
	var_cont* B = stk_pop(ctx->stack);

	var_cont* C = var_eq(A, B);

	C = var_not(C);

	stk_push(ctx->stack, C);

	pc_inc(ctx->pc, 1);
}

void _ins_def_NOT      (rt_t* ctx, bc_cont* line)
{
	var_cont* A = stk_pop(ctx->stack);

	var_cont* C = var_not(A);

	stk_push(ctx->stack, C);

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

/* HELPER FUNCTIONS */
void _ins_def_loop_break(rt_t* ctx)
{
	while (pc_safe(ctx->pc))
	{
		pc_update(ctx->pc);
		pc_inc(ctx->pc, 1);

		if (ctx->pc->line->op == 0x6F)
		{
			break;
		}
	}
}
/* END HELPER FUNCIONS */
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
		_ins_def_loop_break(ctx);
	} else
	{
		pc_inc(ctx->pc, 1);
	}
}
void _ins_def_BREAK    (rt_t* ctx, bc_cont* line)
{
	pc_return(ctx->pc);
	
	_ins_def_loop_break(ctx);
}
void _ins_def_ENDL     (rt_t* ctx, bc_cont* line)
{
	pc_return(ctx->pc);
}

/* HELPER FUNCTIONS */
void _ins_def_branch_to_end_if(rt_t* ctx)
{
	int level = 0;
	while (pc_safe(ctx->pc))
	{
		pc_inc(ctx->pc, 1);
		pc_update(ctx->pc);

		// Is this instruction another IF statement?
		if (ctx->pc->line->op == 0x72)
		{
			// Increment the if statement depth counter
			level++;
		} else
		// Is the instruction an ELSE statement?
		if (ctx->pc->line->op == 0x73)
		{
			// We're done here if we're in our scope
			if (level == 0) break;
		} else
		// Is the instruction a DONE statement?
		if (ctx->pc->line->op == 0x7E)
		{
			// And we're not in another if statement, we're done here
			if (level == 0) break;

			level--;
		}
	}

	pc_inc(ctx->pc, 1);
}
/* END HELPER FUNCTIONS */
void _ins_def_GOTO     (rt_t* ctx, bc_cont* line)
{
	int value = var_data_get_G_INT(line->varg[0]);

	pc_branch(ctx->pc, value);
}
void _ins_def_JUMPF    (rt_t* ctx, bc_cont* line)
{
	int value = var_data_get_G_INT(line->varg[0]);

	pc_inc(ctx->pc, value);
}
void _ins_def_IFDO     (rt_t* ctx, bc_cont* line)
{
	// Get the value off the stack
	var_cont* var = stk_pop(ctx->stack);
	int value = var_data_get_G_INT(var);

	// If the value is false, find an ELSE statement or DONE statement.
	if (value < 1)
	{
		_ins_def_branch_to_end_if(ctx);
	} else
	{
		pc_inc(ctx->pc, 1);
	}
}
void _ins_def_ELSE     (rt_t* ctx, bc_cont* line)
{
	pc_inc(ctx->pc, 1);
	_ins_def_branch_to_end_if(ctx);
}
void _ins_def_DONE     (rt_t* ctx, bc_cont* line)
{
	pc_inc(ctx->pc, 1);
}
void _ins_def_CALL     (rt_t* ctx, bc_cont* line)
{
	int scope = var_data_get_G_INT(line->varg[0]);
	int name  = var_data_get_G_INT(line->varg[1]);

	// Call the function
	proc_function_call(ctx, scope, name);

	pc_inc(ctx->pc, 1);
}

void _ins_def_GETN     (rt_t* ctx, bc_cont* line)
{
	int name = var_data_get_G_INT(line->varg[0]);

	var_cont* obj = stk_pop(ctx->stack);

	ns_t* object = object_get(obj);

	var_cont* var = object_get_name(object, name);

	stk_push(ctx->stack, var);

	pc_inc(ctx->pc, 1);
}
void _ins_def_SETN     (rt_t* ctx, bc_cont* line)
{
	int name = var_data_get_G_INT(line->varg[0]);

	var_cont* obj = stk_pop(ctx->stack);
	var_cont* var = stk_pop(ctx->stack);

	ns_t* object = object_get(obj);
	var_cont* set = var_data_cpy(var);

	object_set_name(object, name, set);

	pc_inc(ctx->pc, 1);
}
void _ins_def_CALLM    (rt_t* ctx, bc_cont* line)
{
	int name = var_data_get_G_INT(line->varg[0]);
	// Pop the stack to get the object
	var_cont* obj = stk_pop(ctx->stack);
	// Get the objects variable data
	ns_t* object = object_get(obj);
	// Get the method to call
	var_cont* var = object_get_name(object, name);
	var_data_func* func = var_data_get_FUNC(var);
	// Push current namespace context
	ns_ctx_push(ctx->varctx, ctx->vars);

	// Set current namespace to objects namespace
	ctx->vars = object;
	// Call the function
	proc_function_call_handle(ctx, func);
	// Update the program counter
	pc_update(ctx->pc);
	// Run code here so we can pop the namespace context
	proc_run_to_return(ctx);
	// Pop the namespace context
	ctx->vars = ns_ctx_pop(ctx->varctx);

	pc_inc(ctx->pc, 1);
}
void _ins_def_INDEXO   (rt_t* ctx, bc_cont* line)
{
	pc_inc(ctx->pc, 1);
}
void _ins_def_MODO     (rt_t* ctx, bc_cont* line)
{
	pc_inc(ctx->pc, 1);
}

void _ins_def_RETURN   (rt_t* ctx, bc_cont* line)
{
	// Pop a level in the stack and arguement stack
	stk_poplevel(&ctx->stack);
	stk_poplevel(&ctx->argstk);

	// Pop the namespace and get the return value
	var_cont* return_value = ns_pop(ctx->vars);

	if (return_value->type != VOID)
	{
		// Push the return value to the stack
		stk_push(ctx->stack, return_value);
	}
	else
	{
		var_del(return_value);
	}

	// Return to the callee
	pc_return(ctx->pc);
}
void _ins_def_NEW      (rt_t* ctx, bc_cont* line)
{
	int scope = var_data_get_G_INT(line->varg[0]);
	int name  = var_data_get_G_INT(line->varg[1]);

	// Get the object builder
	var_cont* var = proc_getvar(ctx, scope, name);
	var_data_objbldr* builder = var_data_get_OBJBLDR(var);

	// Init a new namespace of proper size
	ns_t* new_ns = ns_init(builder->size);

	// Push current namespace to namespace context
	ns_ctx_push(ctx->varctx, ctx->vars);

	// Set the current namespace to new namespace
	ctx->vars = new_ns;

	int offset = 1;
	int i;
	for (i = 0; i < builder->paramlen; i++)
	{
		// Pop the arguement stack
		var_cont* arg = stk_pop(ctx->argstk);

		// Is the arguement of the right type?
		ASSERT(arg->type == builder->param[i], "Invalid arguement stack\n");

		// Declare the name in the new namespace and pass the arguements
		ns_dec(ctx->vars, arg->type, 0, i+offset);
		ns_set(ctx->vars, 0, i+offset, arg);
	}
	// Push new stack levels for the stack and the arguement stack
	stk_newlevel(&ctx->stack);
	stk_newlevel(&ctx->argstk);

	pc_branch(ctx->pc, builder->loc);
}
void _ins_def_ENDCLASS (rt_t* ctx, bc_cont* line)
{
	var_cont* new = var_new(OBJECT);

	var_set(new, ctx->vars, OBJECT);

	ns_dec(ctx->vars, OBJECT, 1, 0);
	ns_set(ctx->vars, 1, 0, new);

	stk_poplevel(&ctx->stack);
	stk_poplevel(&ctx->argstk);

	ctx->vars = ns_ctx_pop(ctx->varctx);

	stk_push(ctx->stack, new);

	pc_return(ctx->pc);
	pc_inc(ctx->pc, 1);
}
void _ins_def_DENS     (rt_t* ctx, bc_cont* line)
{
	int name = var_data_get_G_INT(line->varg[0]);

	ns_t* namespace = ns_init(MAXIMUM_TRACKING_VARS);

	var_cont* ns_var = var_new(OBJECT);
	var_set(ns_var, namespace, OBJECT);

	ns_dec(ctx->names, OBJECT, 1, name);
	ns_set(ctx->names, 1, name, ns_var);

	ctx->vars = namespace;
}
void _ins_def_DECLASS  (rt_t* ctx, bc_cont* line)
{
	int     name = var_data_get_G_INT(line->varg[0]);
	b_type* args = var_data_get_PLIST(line->varg[1]);
	size_t  alen = line->sarg[1];

	// Create a new variable for the object builder
	var_cont* obj = var_new(OBJBLDR);

	// Allocate memory for this variable
	var_data_objbldr* data = var_data_alloc_OBJBLDR();

	// Set this objects ID
	data->id  = name;
	// Set the location
	data->loc = line->real_addr + 1;

	/* Determine namespace size for this object
	 */
	int nsize;
	for (nsize = 0; pc_safe(ctx->pc);)
	{
		// Are we at the end of the object builder?
		if (ctx->pc->line->op == 0xF2)
		{
			break;
		} else
		// Are we declaring a variable or function?
		if (ctx->pc->line->op == 0x20 || ctx->pc->line->op == 0xFF)
		{
			nsize++;
		}

		pc_inc(ctx->pc, 1);
		pc_update(ctx->pc);
	}

	data->end      = ctx->pc->line->real_addr;
	data->size     = nsize + alen + 1;
	data->paramlen = alen;
	data->param    = args;

	// Throw the data in a variable container
	var_set(obj, data, OBJBLDR);

	// Declare a name for this object
	proc_decvar(ctx, OBJBLDR, 1, name);
	// Set the object to the name we just declared
	proc_setvar(ctx, 1, name, obj);

	pc_inc(ctx->pc, 1);
	pc_update(ctx->pc);
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
	/* Determine the namespace size by finding variable declarations in the
	   functions body, Along with determining the end of the function.
	 */
	for (nsize = 0; pc_safe(ctx->pc);)
	{
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

		// Increment the program counter
		pc_inc(ctx->pc, 1);
		pc_update(ctx->pc);
	}

	pc_update(ctx->pc);
	// Set all the values.
	data->end      = ctx->pc->line->real_addr; // This is the end!
	data->size     = nsize + alen + 1;         // How many names will this
	                                           // function have?
	data->type     = type;                     // Return type
	data->paramlen = alen;                     // Set the arguement length
	data->param    = args;                     // Set the parameter list

	// Throw the data in a variable container
	var_set(func, data, FUNC);

	// Declare a name
	proc_decvar(ctx, FUNC, 1, name);
	// Set the name's value to the function we just defined
	proc_setvar(ctx, 1, name, func);

	pc_inc(ctx->pc, 1);
	pc_update(ctx->pc);
}
