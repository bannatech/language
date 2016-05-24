#include <stdlib.h>
#include <stdio.h>

#include "proc.h"

#include "rt.h"
#include "ins_def.h"
#include "bc.h"
#include "stk.h"
#include "var.h"
#include "ns.h"
#include "pc.h"
#include "helper.h"

/* Initializes process, returns runtime context.
 *  char* - Filename of valid bytecode
 */
rt_t* proc_init(char* fname)
{
	N_ASSERT(fname, "proc_init\n");
	rt_t* ctx = rt_ctx_new(fname, stk_new());

	return ctx;
}

/* Starts execution loop for a runtime context
 * rt_t* - Runtime context
 */
void proc_run(rt_t* ctx)
{
	N_ASSERT(ctx, "proc_run\n");

	int n;
	
	for (n = 0; pc_safe(ctx->pc); pc_update(ctx->pc))
	{
		if (ctx->db)
		{
			printf("[%i]:\t", ctx->pc->address);
			bc_print_op(ctx->pc->line);
			printf("\n");
		}

		INS_DEF[ctx->pc->line->op](ctx, ctx->pc->line);

		n++;
	}
}

/* Runs exection loop until a return is reached
 */
void proc_run_to_return(rt_t* ctx)
{
	N_ASSERT(ctx, "proc_run\n");

	int n;
	for (n = 0; pc_safe(ctx->pc); pc_update(ctx->pc))
	{
		if (ctx->db)
		{
			printf("[%i]:\t", ctx->pc->address);
			bc_print_op(ctx->pc->line);
			printf("\n");
		}

		if (ctx->pc->line->op == 0x7F)
		{
			n++;
		}

		INS_DEF[ctx->pc->line->op](ctx, ctx->pc->line);

		// Break when the function returns
		
		if (ctx->pc->line->op == 0xF0)
		{
			if (n > 0)
			{
				n--;
			} else
			{
				break;
			}
		}
	}
}

/* Calls runtime context elements to free memory and terminate
 *  rt_t* - Runtime context
 */
void proc_clean(rt_t* ctx)
{
	N_ASSERT(ctx, "proc_clean\n");
	rt_ctx_del(ctx);
}

/* Set a variable subroutine
 *  rt_t*     - Runtime context
 *  b_type    - Type
 *  int       - Scope
 *  ns_addr   - Name of variable
 *
 *  This function is used to support an interface to multithreaded instances
 */
void proc_decvar(rt_t* ctx, b_type type, int scope, ns_addr name)
{
	N_ASSERT(ctx, "proc_decvar\n");

	int x = (scope & 0xFE) >> 1;
	int s = (scope & 0x01);

	if (x == 0)
	{
		ns_dec(ctx->vars, type, s, name);
	}
}

/* Set a variable subroutine
 *  rt_t*     - Runtime context
 *  int       - Scope
 *  ns_addr   - Name of variable
 *  var_cont* - Variable container
 *
 *  This function is used to support an interface to multithreaded instances
 */
void proc_setvar(rt_t* ctx, int scope, ns_addr name, var_cont* var)
{
	N_ASSERT(ctx, "proc_setvar\n");

	int x = (scope & 0xFE) >> 1;
	int s = (scope & 0x01);

	if (x == 0)
	{
		ns_set(ctx->vars, s, name, var);
	} else
	{
		var_cont* ns_var = ns_get(ctx->names, 1, x);
		var_data_object* var_d = var_data_get_OBJECT(ns_var);
		ns_t* ns = (ns_t*) var_d->ref;

		ns_set(ns, s, name, var);
	}
}

/* Get a variable subroutine
 *  rt_t*   - Runtime context
 *  int     - Scope
 *  ns_addr - Name of variable
 */
var_cont* proc_getvar(rt_t* ctx, int scope, ns_addr name)
{
	N_ASSERT(ctx, "proc_getvar\n");
	var_cont* rv;

	int x = (scope & 0xFE) >> 1;
	int s = (scope & 0x01);

	if (x == 0)
	{
		rv = ns_get(ctx->vars, scope, name);
	} else
	{
		var_cont* ns_var = ns_get(ctx->names, 1, x);
		var_data_object* var_d = var_data_get_OBJECT(ns_var);
		ns_t* ns = (ns_t*) var_d->ref;

		rv = ns_get(ns, s, name);
	}

	return rv;
}

/* Call a function
 */
void proc_function_call(rt_t* ctx, int scope, ns_addr name)
{
	N_ASSERT(ctx, "proc_function_call\n");

	int x = (scope & 0xFE) >> 1;

	var_cont* var = proc_getvar(ctx, scope, name);

	if (x != 0)
	{
		ns_ctx_push(ctx->varctx, ctx->vars);

		var_cont* ns_var = ns_get(ctx->names, 1, x);
		var_data_object* var_d = var_data_get_OBJECT(ns_var);
		ns_t* ns = (ns_t*) var_d->ref;

		ctx->vars = ns;
	}

	var_data_func* func = var_data_get_FUNC(var);
	
	proc_function_call_handle(ctx, func);

	pc_update(ctx->pc);

	proc_run_to_return(ctx);

	if (x != 0)
	{
		ctx->vars = ns_ctx_pop(ctx->varctx);
	}
}

/* Handles arguements and namespace procedures for a given
 * function call
 */
void proc_function_call_handle(rt_t* ctx, var_data_func* func)
{
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
		ASSERT(arg->type == func->param[i], "Invalid arguement stack\n");

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

