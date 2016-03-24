#include <stdlib.h>

#include "rt.h"

#include "bc.h"
#include "stk.h"
#include "var.h"
#include "ns.h"
#include "pc.h"
#include "helper.h"

/* Creates new runtime context.
 *  char*   - Filename
 *  stk_t*  - Arguement stack (non-null)
 *  ns_cont*- Copy of the global namespace
 */
rt_t* rt_ctx_new(char* fname, stk_t* args)
{
	N_ASSERT(fname, "rt_ctx_new\n");
	N_ASSERT(args, "rt_ctx_new\n");

	rt_t* ctx = (rt_t*)malloc(sizeof(rt_t));
	M_ASSERT(ctx);

	ctx->pc     = pc_new(fname);
	ctx->stack  = stk_new();
	ctx->vars   = ns_init(1024);
	ctx->argstk = args;

	return ctx;
}

/* Destroys runtime context. This can be *very* slow.
 */
void rt_ctx_del(rt_t* ctx)
{
	N_ASSERT(ctx, "rt_ctx_del\n");

	N_ASSERT(ctx->stack, "rt_ctx_del\n");
	stk_del(ctx->stack);

	N_ASSERT(ctx->argstk, "rt_ctx_del\n");
	stk_del(ctx->argstk);

	N_ASSERT(ctx->vars, "rt_ctx_del\n");
	ns_del(ctx->vars);

	N_ASSERT(ctx->pc, "rt_ctx_del\n");
	pc_del(ctx->pc);
}
