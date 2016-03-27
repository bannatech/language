#include <stdlib.h>

#include "ns.h"
#include "var.h"
#include "helper.h"

/* Initialize namespace container of size
 *  ns_addr - name limit
 *  int     - Namespace level
 */
ns_cont* ns_cont_init(ns_addr size, int level)
{
	ns_cont* new = (ns_cont*)malloc(sizeof(ns_cont));
	M_ASSERT(new);

	new->names = (var_cont**)malloc(sizeof(var_cont*)*size);
	M_ASSERT(new->names);

	new->size = size;
	new->level = level;

	for (int i = 0; i < size; i++)
	{
		new->names[i] = NULL;
	}

	new->next = NULL;

	return new;
}

/* Initializes namespace of size
 *  ns_addr - name limit
 */
ns_t* ns_init(ns_addr size)
{
	ns_t* ns = (ns_t*)malloc(sizeof(ns_t));
	M_ASSERT(ns);
	
	ns->root = ns_cont_init(size, 0);
	ns->last = ns->root;

	return ns;
}

/* Cleans up memory, returns variable with label to_return
 */
var_cont* ns_cont_del(ns_cont* container, ns_addr to_return)
{
	N_ASSERT(container, "ns_cont_del\n");
	N_ASSERT(container->names, "ns_cont_del\n");

	var_cont* rv;

	for (int i = 0; i < container->size; i++)
	{
		if (container->names[i] != NULL && i != to_return)
		{
			if (container->names[i]->ownership == container->level)
			{
				var_del(container->names[i]);
			}
		}
		else if (i == to_return)
		{
			if (container->names[i] != NULL)
			{
				rv = container->names[i];
				if (rv->ownership == container->level)
				{
					rv->ownership = -1;
				}
			}
		}
	}
	
	free(container->names);

	free(container);

	return rv;
}

/* Cleans up memory
 */
void ns_del(ns_t* ns)
{
	N_ASSERT(ns, "ns_del\n");

	var_cont* var;
	if (ns->last != NULL)
	{
		while (ns->last->next != NULL)
		{
			var = ns_pop(ns);
			if (var != NULL)
			{
				var_del(var);
			}
		}
	}
	
	free(ns);
}

/* Pushes namespace of size
 * ns_t*   - namespace instance
 * ns_addr - name limit
 */
void ns_push(ns_t* ns, ns_addr size)
{
	N_ASSERT(ns, "ns_push\n");

	ns_cont* new = ns_cont_init(size, ns->last->level + 1);

	new->next = ns->last;
	ns->last = new;
}

/* Pops last namespace level
 */
var_cont* ns_pop(ns_t* ns)
{
	N_ASSERT(ns, "ns_pop\n");

	var_cont* rv;
	if (ns->last->next != NULL) {
		ns_cont* newlast = ns->last->next;

		rv = ns_cont_del(ns->last, 0);

		ns->last = newlast;
	}
	return rv;
}

/* Declares a variable, at root or last namespace
 *  ns_t*     - Namespace instance
 *  b_type    - Type of variable
 *  int       - Mux value         [0]
 *  ns_addr   - Variable name
 *
 * @param[0] = namespace level
 *  0 -> current namespace
 *  1 -> global namespace
 */
void ns_dec(ns_t* ns, b_type type, int scope, ns_addr address)
{
	N_ASSERT(ns, "ns_dec\n");

	ns_cont* scoped_ns = scope ? ns->root : ns->last;

	ns_cont_dec(scoped_ns, type, address);
}

/* Declares a variable, at namespace
 *  ns_t*     - Namespace instance
 *  b_type    - Type of variable
 *  ns_addr   - Variable name
 */

void ns_cont_dec(ns_cont* container, b_type type, ns_addr address)
{
	N_ASSERT(container, "ns_cont_dec\n");

	SIZE_ASSERT( container->size > address );

	container->names[ address ] = var_new(type);
	container->names[ address ]->ownership = container->level;
}

/* Sets variable to value, at root or last namespace
 *  ns_t*     - namespace instance
 *  int       - mux value         [0]
 *  ns_addr   - Variable name
 *  var_cont* - Variable
 *
 * @param[0] = namespace level
 * * 0 -> current namespace
 * * 1 -> global namespace
 */
void ns_set(ns_t* ns, int scope, ns_addr address, var_cont* var)
{
	N_ASSERT(ns, "ns_set\n");
	N_ASSERT(var, "ns_set\n");

	ns_cont* scoped_ns = scope ? ns->root : ns->last;

	ns_cont_set(scoped_ns, var, address);
}

/* Sets variable to value, at root or last namespace
 *  ns_cont*  - Namespace instance
 *  var_cont* - Variable
 *  ns_addr   - Variable name
 */
void ns_cont_set(ns_cont* container, var_cont* var, ns_addr address)
{
	N_ASSERT(container, "ns_cont_set\n");
	N_ASSERT(var, "ns_cont_set\n");
	SIZE_ASSERT( container->size > address );
	N_ASSERT(container->names[ address ], "Attempt to set an undeclared variable\n");

	if (var->ownership < 0)
	{
		var->ownership = container->level;
	}

	container->names[ address ]->ownership = var->ownership;

	var_set(container->names[ address ], var->data, var->type);
}

/* Gets variable from address

 *  ns_t*     - namespace instance
 *  int       - mux value         [0]
 *  ns_addr   - Variable name
 *
 * @param[0] = namespace level
 *  0 -> current namespace
 *  1 -> global namespace
 */
var_cont* ns_get(ns_t* ns, int scope, ns_addr address)
{
	N_ASSERT(ns, "ns_get\n");

	ns_cont* scoped_ns = scope ? ns->root : ns->last;

	return ns_cont_get(scoped_ns, address);
}

/* Gets variable from address
 *  ns_t*     - namespace instance
 *  ns_addr   - Variable name
 */
var_cont* ns_cont_get(ns_cont* container, ns_addr address)
{
	N_ASSERT(container, "ns_cont_get\n");
	SIZE_ASSERT( container->size > address );

	return container->names[ address ];
}
