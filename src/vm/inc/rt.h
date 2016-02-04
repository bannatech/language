/* `rt.h` handles runtime management
 */

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
	stk_t*     stack;
	ns_t*      vars;
	ns_addr    func;
	thread_t*  thread_ctx;
} rt_worker

/* Initializes runtime environment, spawns main thread and 
 *
 */
rt_info* rt_init(char);

ns_t* rt_init_ns(bc_cont*);

rt_worker* rt_spawnthread(rt_info*, ns_addr);

void rt_runthread(rt_info*, rt_worker*);

void* rt_workerfun(void*);
