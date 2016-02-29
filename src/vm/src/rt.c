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
	N_ASSERT(fname);
	N_ASSERT(args);

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
	N_ASSERT(ctx);

	N_ASSERT(ctx->stack);
	stk_del(ctx->stack);

	N_ASSERT(ctx->argstk);
	stk_del(ctx->argstk);

	N_ASSERT(ctx->vars);
	ns_del(ctx->vars);

	N_ASSERT(ctx->pc);
	pc_del(ctx->pc);
}

#ifdef THREADING

#include <pthread.h>
rt_pool* rt_pool_init(int depth)
{

}

void rt_pool_kill(rt_pool* pool)
{

}

void *rt_worker_run(void* ctx)
{
	rt_worker* c;
	c = (rt_worker*)ctx;

	//TODO this.

	return 0;
}


rt_worker* rt_worker_new(char* fname, ns_addr func, ns_cont* gs, stk_t* args)
{
	rt_worker* worker = (rt_worker*)malloc(sizeof(rt_worker));
	M_ASSERT(worker);

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

#endif // SINGLE_THREAD
