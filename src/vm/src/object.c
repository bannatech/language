#include <stdlib.h>

#include "object.h"

#include "ns.h"

#include "helper.h"

obj_t* object_init()
{
	obj_t* rv = (obj_t*)malloc(sizeof(obj_t));
	M_ASSERT(rv);

	rv->names    = NULL;

	return rv;
}

void object_del(void* object)
{
	N_ASSERT(object, "object_del\n");

	obj_t* o = object;
	
	if (o->names != NULL)
		ns_del(o->names);
	
	free(o);
}
