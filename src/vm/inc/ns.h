/* `ns` Namespace implementation
 */

#ifndef NS_H
#define NS_H

#include <stdlib.h>

#include "var.h"
#include "helper.h"

typedef int ns_addr;

typedef struct ns_cont {
	ns_addr    size;
	var_cont** names;
	struct ns_cont* next;
} ns_cont;

typedef struct ns_t {
	ns_cont* root;
	ns_cont* last;
} ns_t;

ns_cont* ns_cont_init(ns_addr);

/* Initializes namespace of size
 */
ns_t* ns_init(ns_addr);

void ns_cont_del(ns_cont*);

/* Cleans up memory
 */
void ns_del(ns_t*);

/* Pushes namespace of size
 */
void ns_push(ns_t*, int);

/* Pops last namespace level
 */
void ns_pop(ns_t*);

void ns_cont_dec(ns_cont*, b_type, ns_addr);

/* Declares a variable, at root or last namespace
 */
void ns_dec(ns_t*, b_type, int, ns_addr);

void ns_cont_set(ns_cont*, var_cont*, ns_addr);

/* Sets variable to value, at root or last namespace
 */
void ns_set(ns_t*, int, ns_addr, var_cont*);

var_cont* ns_cont_get(ns_cont*, ns_addr);

/* Gets variable from address
 */
var_cont* ns_get(ns_t*, int, ns_addr);

#endif // NS_H