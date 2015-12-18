/* `ns` Namespace implementation
 *
 * Each variable that exists and accessed will be via a level on a namespace
 * instance. For example, at the root of a program, a namespace is initialized
 * and variables declared at this level are accessable everywhere. When a func
 * is called, a new namespace level is initialized and variables declared on
 * that level will be destroyed/inaccessable when the function returns and the 
 * new level is 'popped', going up a level.
 *
 * When a variable is queued, it will search through all the levels of the
 * namespace to retreive the proper value.
 */

#ifndef NS_H
#define NS_H

#include <stdlib.h>

#include "types.h"

typedef struct ns_t {
	void* placeholder;
} ns_t;

/* Initializes namespace.
 */
ns_t* ns_init(void);

/* Initializes new namspace level.
 */
void ns_new(ns_t*);

/* Pushes new namespace level to a pre-initialized state
 */
void ns_push(ns_t*, ns_t*);

/* Pops last namespace level. Destroys all data initialized at level.
 */
void ns_pop_del(ns_t*);

/* Pops last namespace level. Keeps data, returns pointer.
 */
ns_t* ns_pop(ns_t*);

/* Declares a variable of name char*.
 * Return code denotes a success or failure. (bool)
 */
int ns_dec(ns_t*, char*);

/* Sets variable to value.
 * Return code denotes a success or failure. (bool)
 */
int ns_set(ns_t*, char*, var_cont*);

#endif // NS_H
