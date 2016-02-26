/* `rt.h` handles runtime management
 */

#ifndef RT_H
#define RT_H

#include <stdlib.h>
#include <stdio.h>

#include "bc.h"
#include "stk.h"
#include "var.h"
#include "pc.h"
#include "helper.h"

#ifdef THREADING
#include <pthread.h>

typedef struct rt_pool {
	int         thread_count;
	rt_worker** threads;
	ns_cont*    gvars;
} rt_pool;


typedef struct rt_worker {
	pthread_t* thread_ctx;
	rt_t       runtime_ctx;
} rt_worker

#endif // THREADING

typedef struct rt_t {
	pc_t*      pc;
	stk_t*     stack;
	stk_t*     argstk;
	ns_t*      vars;
	ns_cont*   gvars;
} rt_t;

#ifdef THREADING

rt_pool* rt_pool_init(int);

void rt_pool_kill(rt_pool*);

void *rt_worker_run(void*);

rt_worker* rt_worker_new(void);

void rt_worker_del(rt_worker*);

#endif //THREADING

rt_t* rt_ctx_new(char*, stk_t*, ns_cont*);

void rt_ctx_del(rt_t*);

#endif // RT_H
