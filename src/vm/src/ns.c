#include <stdlib.h>

#include "ns.h"
#include "var.h"
#include "helper.h"

ns_t* ns_init(int size)
{
	ns_t* ns = (ns_t*)malloc(sizeof(ns_t));
	ASSERT(ns != NULL, "Could not allocate memory\n");
	
	ns->root = ns_cont_init(size);
	ns->last = NULL;

	return ns;
}

ns_cont* ns_cont_init(int size)
{
	ns_cont* new = (ns_cont*)malloc(sizeof(ns_cont));
	ASSERT(new != NULL, "Could not allocate memory\n");

	new->names = (var_cont**)malloc(sizeof(var_cont*)*size);
	ASSERT(new->names != NULL, "Could not allocate memory\n");

	new->size = size;

	for (int i = 0; i < size; i++)
	{
		new->names[i] = NULL;
	}

	new->next = NULL;

	return new;
}

void ns_del(ns_t* ns)
{
	while (ns->last->next != NULL)
		ns_pop(ns);
	
	free(ns);
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

void ns_push(ns_t* ns, int size)
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

void ns_dec(ns_t* ns, b_type type, int scope, int name)
{
	return;
}

void ns_set(ns_t* ns, int scope, int name, var_cont* data)
{
	return;
}

