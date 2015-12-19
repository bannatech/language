#include <stdlib.h>

#include "ns.h"
#include "types.h"
#include "helper.h"

ns_t* ns_init(void)
{
	ns_t* namespace = (ns_t*)malloc(sizeof(ns_t));
	ASSERT(namespace != NULL, "Could not allocate memory\n");

	return namespace;
}

void ns_new(ns_t* namespace)
{
	return;
}

void ns_push(ns_t* namespace, ns_t* namespace_append)
{
	return;
}

void ns_pop_del(ns_t* namespace)
{
	return;
}

ns_t* ns_pop(ns_t* namespace)
{
	return namespace;
}

int ns_dec(ns_t* namespace, char* name)
{
	return 0;
}

int ns_set(ns_t* namespace, char* name, var_cont* data)
{
	return 0;
}

