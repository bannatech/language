#include <stdlib.h>

#include "ns.h"
#include "var.h"
#include "helper.h"

ns_cont* ns_cont_init(ns_addr size)
{
	ns_cont* new = (ns_cont*)malloc(sizeof(ns_cont));
	M_ASSERT(new);

	new->names = (var_cont**)malloc(sizeof(var_cont*)*size);
	M_ASSERT(new->names);

	new->size = size;

	for (int i = 0; i < size; i++)
	{
		new->names[i] = NULL;
	}

	new->next = NULL;

	return new;
}

ns_t* ns_init(ns_addr size)
{
	ns_t* ns = (ns_t*)malloc(sizeof(ns_t));
	M_ASSERT(ns);
	
	ns->root = ns_cont_init(size);
	ns->last = NULL;

	return ns;
}

void ns_cont_del(ns_cont* container)
{
	for (int i = 0; i < container->size; i++)
	{
		if (container->names[i] != NULL)
			var_del(container->names[i]);
	}
	
	free(container->names);

	free(container);
}

void ns_del(ns_t* ns)
{
	M_ASSERT(ns);
	if (ns->last != NULL)
		while (ns->last->next != NULL)
			ns_pop(ns);
	
	free(ns);
}

void ns_push(ns_t* ns, ns_addr size)
{
	ns_cont* new = ns_cont_init(size);

	if (ns->last == NULL)
	{
		new->next = ns->root;
		ns->last = new;
	}
	else
	{
		new->next = ns->last;
		ns->last = new;
	}
}

void ns_pop(ns_t* ns)
{
	if (ns->last->next != NULL) {
		ns_cont* newlast = ns->last->next;

		ns_cont_del(ns->last);

		ns->last = newlast;
	}
}

void ns_cont_dec(ns_cont* ns, b_type type, ns_addr address)
{
	SIZE_ASSERT( ns->size > address );

	ns->names[ address ] = var_new(type);
}

void ns_dec(ns_t* ns, b_type type, int scope, ns_addr address)
{
	ns_cont* scoped_ns = scope ? ns->root : ns->last;

	ns_cont_dec(scoped_ns, type, address);
}

void ns_cont_set(ns_cont* ns, var_cont* var, ns_addr address)
{
	SIZE_ASSERT( ns->size > address );

	var_set(ns->names[ address ], var->data, var->type);
}

void ns_set(ns_t* ns, int scope, ns_addr address, var_cont* var)
{
	ns_cont* scoped_ns = scope ? ns->root : ns->last;

	ns_cont_set(scoped_ns, var, address);
}

var_cont* ns_cont_get(ns_cont* ns, ns_addr address)
{
	SIZE_ASSERT( ns->size > address );

	return ns->names[ address ];
}

var_cont* ns_get(ns_t* ns, int scope, ns_addr address)
{
	ns_cont* scoped_ns = scope ? ns->root : ns->last;

	return ns_cont_get(scoped_ns, address);
}
