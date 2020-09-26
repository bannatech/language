#include <stdlib.h>

#include "object.h"

#include "ns.h"
#include "var.h"

#include "helper.h"

ns_t* object_get(var_cont* object)
{
	N_ASSERT(object, "object_get\n");

	return (ns_t*)object->data;
}

void object_del(void* object)
{
	N_ASSERT(object, "object_del\n");

	ns_t* o = object;

	ns_del(o);
}

var_cont* object_get_name(ns_t* object, ns_addr name)
{
	N_ASSERT(object, "object_get_name\n");

	var_cont* value = ns_get(object, 1, name);
	
	return value;
}

void object_set_name(ns_t* object, ns_addr name, var_cont* var)
{
	N_ASSERT(object, "object_set_name\n");
	N_ASSERT(var, "object_set_name\n");

	ns_set(object, 1, name, var);
}
