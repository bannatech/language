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
	N_ASSERT(fname);
	rt_t* ctx = rt_ctx_new(fname, stk_new());

	return ctx;
}

/* Starts execution loop for a runtime context
 * rt_t* - Runtime context
 */
void proc_run(rt_t* ctx)
{
	N_ASSERT(ctx);
	
	for (pc_branch(ctx->pc, 0); pc_safe(ctx->pc); pc_update(ctx->pc))
	{
		ins_def_is_valid(ctx->pc->line);
		INS_DEF[ctx->pc->line->op](ctx, ctx->pc->line->args);
	}
}

/* Calls runtime context elements to free memory and terminate
 *  rt_t* - Runtime context
 */
void proc_clean(rt_t* ctx)
{
	N_ASSERT(ctx);
	rt_ctx_del(ctx);
}

/* Function call subroutine.
 *  rt_t*     - Runtime context
 *  var_cont* - Variable in type of function
 *
 *  This function is used to support an interface to multithreaded instances
 */
var_cont* proc_callfun(rt_t* ctx, var_cont* func)
{
	N_ASSERT(ctx);
	return 0;
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

}

/* Get a variable subroutine
 *  rt_t*   - Runtime context
 *  int     - Scope
 *  ns_addr - Name of variable
 */
var_cont* proc_getvar(rt_t* ctx, int scope, ns_addr name)
{
	return 0;
}

