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
	ns_dec(ctx->vars, type, scope, name);
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
	ns_set(ctx->vars, scope, name, var);
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

	rv = ns_get(ctx->vars, scope, name);

	return rv;
}

