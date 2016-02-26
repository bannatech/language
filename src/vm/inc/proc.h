/* `proc.h` - Provide running process to evaluate bytecode
 */

#ifndef PROC_H
#define PROC_H

#include <stdlib.h>
#include <stdio.h>

#include "rt.h"
#include "bc.h"
#include "stk.h"
#include "var.h"
#include "pc.h"
#include "helper.h"

rt_t* proc_init(char*);

void proc_run(rt_t*);

void proc_clean(rt_t*);

var_cont* proc_callfun(rt_t*, var_cont*);

void proc_setvar(rt_t*, int, ns_addr, var_cont*);

var_cont* proc_getvar(rt_t*, int, ns_addr);

#endif //PROC_H
