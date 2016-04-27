/* `object.h` Object implementation
 */

#ifndef OBJECT_H
#define OBJECT_H

#include <stdlib.h>

#include "ns.h"

#include "helper.h"

typedef struct obj_t {
	ns_t* names;
	ns_addr mod_ops[0x100];
} obj_t;

/* Initalize an empty object of size
 */
obj_t* object_init();

/* Deconstruct an object
 */
void object_del(void*);

#endif // OBJECT_H
