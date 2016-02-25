/* `rt.h` handles runtime management
 */

#ifndef RT_H
#define RT_H

#include <stdlib.h>
#include <stdio.h>

#include "bc.h"
#include "stk.h"
#include "var.h"
#include "threads.h"
#include "helper.h"

typedef struct rt_info {
	int         thread_count;
	rt_worker** threads;
	bc_cont*    code;
	ns_t*       vars;
} rt_info;

typedef struct rt_worker {
	thrd_state state;
	thread_t*  thread_ctx;
} rt_worker

typedef struct rt_context {
	stk_t*     stack;
	stk_t*     argstk;
	ns_t*      vars;
	ns_addr    func;
} rt_context;

/* Initializes runtime environment, spawns main thread and
 *
 */
rt_info* rt_init(char);

ns_t* rt_init_ns(bc_cont*);

rt_worker* rt_spawnthread(rt_info*, ns_addr);

void rt_runthread(rt_info*, rt_worker*);

void* rt_workerfun(void*);

#endif // RT_H
