#include <stdlib.h>
#include <stdio.h>

#include "proc.h"

#include "rt.h"
#include "ins_def.h"
#include "bc.h"
#include "stk.h"
#include "var.h"
#include "pc.h"
#include "helper.h"

rt_t* proc_init(char* fname)
{
	N_ASSERT(fname);
	rt_t* ctx = rt_ctx_new(fname, stk_new(), ns_cont_new(1024));

	return ctx;
}

void proc_run(rt_t* ctx)
{
	N_ASSERT(ctx);
	
	for (pc_branch(ctx->pc, 0); pc_safe(ctx->pc); pc_update(ctx->pc))
	{
		ins_def_is_valid(ctx->pc->line);
		INS_DEF[ctx->pc->line->op](ctx, ctx->pc->line->args);
	}
}

void proc_clean(rt_t* ctx)
{
	N_ASSERT(ctx);
	rt_ctx_del(ctx);
}

var_cont* proc_callfun(rt_t* ctx, var_cont* func)
{
	N_ASSERT(ctx);
	
}

void proc_setvar(rt_t* ctx, int scope, ns_addr name, var_cont* var)
{
	
}

var_cont* proc_getvar(rt_t* ctx, int scope, ns_addr name)
{
	
}


