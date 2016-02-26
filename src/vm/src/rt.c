#include <stdlib.h>
#include <pthreads.h>

#include "rt.h"
#include "bc.h"
#include "stk.h"
#include "var.h"
#include "pc.h"
#include "helper.h"

rt_pool* rt_pool_init(int depth)
{

}

void rt_pool_kill(rt_pool* pool)
{

}


rt_worker* rt_worker_new(char* fname, ns_addr func, ns_cont* gscope, stk_t* args)
{
	rt_worker* worker = (rt_worker*)malloc(sizeof(rt_worker));
	M_ASSERT(worker);

	worker->pc = pc_new(fname);

	worker->runtime_ctx = rt_ctx_init(func, args, gscope, 1024);

	pthread_create(&worker->thread_ctx, NULL, rt_worker_run, worker);

	return worker;
}

void rt_worker_del(rt_worker* worker)
{
	N_ASSERT(worker);
	N_ASSERT(worker->thread_ctx);
	pthread_cancel(worker->thread_ctx);

	N_ASSERT(worker->runtime_ctx);
	rt_ctx_del(worker->runtime_ctx);

	N_ASSERT(worker->pc);
	pc_del(worker->pc);

	free(worker);
}

rt_t* rt_ctx_new(ns_addr func, stk_t* args, ns_cont* gscope, int size)
{
	rt_t* ctx = (rt_t*)malloc(sizeof(rt_t));
	M_ASSERT(ctx);

	ctx->stack  = stk_new();
	ctx->argstk = args;
	ctx->vars   = ns_new(size);
	ctx->gvars  = gscope;
	ctx->entry  = func;

	return ctx;
}

void rt_ctx_del(rt_t* ctx)
{
	N_ASSERT(ctx);

	N_ASSERT(ctx->stack);
	if (ctx->stack != NULL)
		stk_del(ctx->stack);

	N_ASSERT(ctx->argstk);
	if (ctx->argstk != NULL)
		stk_del(ctx->stack);

	N_ASSERT(ctx->ns);
	if (ctx->ns != NULL)
		ns_del(ctx->ns);
}

void *rt_worker_run(void* ctx)
{
	rt_worker* c;
	c = (rt_worker*)ctx;

	//TODO actually make this run the function that runs opcodes n' what not

	return 0;
}
