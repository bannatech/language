/* `rt.h` handles runtime management
 */

#ifndef RT_H
#define RT_H

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#include "bc.h"
#include "stk.h"
#include "var.h"
#include "pc.h"
#include "helper.h"

typedef struct rt_pool {
	int         thread_count;
	rt_worker** threads;
	ns_cont*    gvars;
} rt_pool;

typedef struct rt_worker {
	pthread_t* thread_ctx;
	rt_t       runtime_ctx;
	pc_t*      pc;
} rt_worker

typedef struct rt_t {
	stk_t*     stack;
	stk_t*     argstk;
	ns_t*      vars;
	ns_cont*   gvars;
	ns_addr    entry;
} rt_t;

rt_pool* rt_pool_init(int);

void rt_pool_kill(rt_pool*);

rt_worker* rt_worker_new(void);

void rt_worker_del(rt_worker*);

rt_t* rt_ctx_new(char);

void rt_ctx_del(rt_t*);

void *rt_worker_run(void*);

#endif // RT_H
