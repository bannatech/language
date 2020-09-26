/* `object.h` Object implementation
 */

#ifndef OBJECT_H
#define OBJECT_H

#include <stdlib.h>

#include "ns.h"

#include "helper.h"

ns_t* object_get(var_cont*);

/* Deconstruct an object
 */
void object_del(void*);

var_cont* object_get_name(ns_t*, ns_addr);

void object_set_name(ns_t*, ns_addr, var_cont*);

#endif // OBJECT_H
