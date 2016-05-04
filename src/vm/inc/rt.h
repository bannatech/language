/* `rt.h` handles runtime management
 */

#ifndef RT_H
#define RT_H

#include <stdlib.h>
#include <stdio.h>

#include "bc.h"
#include "stk.h"
#include "var.h"
#include "object.h"
#include "ns.h"
#include "pc.h"
#include "helper.h"

/* Runtime context structure
 *  pc    - `pc.h` program counter instance
 *  stack - `stk.h` stack instance[0]
 *  argstk- `stk.h` stack instance[1]
 *  vars  - `ns.h` namespace instance
 *
 *  [0] This is the stack register used at runtime to push/pop variable
 *      containers.
 *  [1] Function calls implement this stack to load variables as arguements.
 */
typedef struct rt_t {
	int     db;
	pc_t*   pc;
	stk_t*  stack;
	stk_t*  argstk;
	ns_t*   vars;
	ns_ctx* varctx;
	ns_t*   names;
} rt_t;

/* Creates new runtime context.
 *  char*   - Filename
 *  stk_t*  - Arguement stack
 */
rt_t* rt_ctx_new(char*, stk_t*);

void rt_ns_del(void*);

/* Destroys runtime context.
 */
void rt_ctx_del(rt_t*);

#endif // RT_H
