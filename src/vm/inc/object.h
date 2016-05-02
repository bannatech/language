/* `object.h` Object implementation
 */

#ifndef OBJECT_H
#define OBJECT_H

#include <stdlib.h>

#include "ns.h"
#include "var.h"

#include "helper.h"

typedef struct obj_t {
	ns_t* names;
} obj_t;

/* Initalize an empty object of size
 */
obj_t* object_init();

/* Deconstruct an object
 */
void object_del(void*);

var_cont* object_get_name(obj_t*, ns_addr);

void object_set_name(obj_t*, ns_addr, var_cont*);

var_cont* object_call_method(obj_t*, ns_addr);

#endif // OBJECT_H
