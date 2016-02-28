/* `rt.h` handles runtime management
 */

#ifndef RT_H
#define RT_H

#include <stdlib.h>
#include <stdio.h>

#include "bc.h"
#include "stk.h"
#include "var.h"
#include "ns.h"
#include "pc.h"
#include "helper.h"

/* Runtime context structure
 *  pc    - `pc.h` program counter instance
 *  stack - `stk.h` stack instance[0]
 *  argstk- `stk.h` stack instance[1]
 *  vars  - `ns.h` namespace instance
 *  gvars - `ns.h` namespace container instance
 *
 *  [0] This is the stack register used at runtime to push/pop variable containers.
 *  [1] Function calls implement this stack to load variables as arguements.
 */
typedef struct rt_t {
	pc_t*      pc;
	stk_t*     stack;
	stk_t*     argstk;
	ns_t*      vars;
} rt_t;

/* Creates new runtime context.
 *  char*   - Filename
 *  stk_t*  - Arguement stack
 *  ns_cont*- Copy of the global namespace
 */
rt_t* rt_ctx_new(char*, stk_t*);

/* Destroys runtime context. This can be *very* slow.
 */
void rt_ctx_del(rt_t*);


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

#ifdef THREADING

rt_pool* rt_pool_init(int);

void rt_pool_kill(rt_pool*);

void *rt_worker_run(void*);

rt_worker* rt_worker_new(void);

void rt_worker_del(rt_worker*);

#endif //THREADING
#endif // RT_H
