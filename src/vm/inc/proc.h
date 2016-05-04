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
#include "ns.h"
#include "pc.h"
#include "helper.h"

/* Initializes process, returns runtime context.
 *  char* - Filename of valid bytecode
 */
rt_t* proc_init(char*);

/* Starts execution loop for a runtime context
 */
void proc_run(rt_t*);

void proc_run_to_return(rt_t*);

/* Calls runtime context elements to free memory and terminate
 *  rt_t* - Runtime context
 */
void proc_clean(rt_t*);

/* Set a variable subroutine
 *  rt_t*     - Runtime context
 *  int       - Scope
 *  ns_addr   - Name of variable
 *
 *  This function is used to support an interface to multithreaded instances
 */
void proc_decvar(rt_t*, b_type, int, ns_addr);

/* Set a variable subroutine
 *  rt_t*     - Runtime context
 *  int       - Scope
 *  ns_addr   - Name of variable
 *  var_cont* - Variable container
 *
 *  This function is used to support an interface to multithreaded instances
 */
void proc_setvar(rt_t*, int, ns_addr, var_cont*);

/* Get a variable subroutine
 *  rt_t*   - Runtime context
 *  int     - Scope
 *  ns_addr - Name of variable
 *
 *  This function is used to support an interface to multithreaded instances
 */
var_cont* proc_getvar(rt_t*, int, ns_addr);

void proc_function_call(rt_t*, int, ns_addr);

void proc_function_call_handle(rt_t*, var_data_func*);

#endif //PROC_H
