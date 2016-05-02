#include <stdlib.h>

#include "object.h"

#include "ns.h"
#include "var.h"

#include "helper.h"

obj_t* object_init()
{
	obj_t* rv = (obj_t*)malloc(sizeof(obj_t));
	M_ASSERT(rv);

	rv->names = NULL;

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

obj_t* object_get(void* object)
{
	N_ASSERT(object, "object_get\n");

	obj_t* o = object;

	return o;
}

var_cont* object_get_name(obj_t* object, ns_addr name)
{
	N_ASSERT(object, "object_get_name\n");

	var_cont* value = ns_get(object->names, 1, name);
	
	return value;
}

void object_set_name(obj_t* object, ns_addr name, var_cont* var)
{
	N_ASSERT(object, "object_set_name\n");
	N_ASSERT(var, "object_set_name\n");

	ns_set(object->names, 1, name, var);
}

var_cont* object_call_method(obj_t* object, ns_addr name)
{
	N_ASSERT(object, "object_call_method\n");

	var_cont* rv = NULL;

	return rv;
}
