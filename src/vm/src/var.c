#include <stdlib.h>
#include <stdio.h>

#include "var.h"
#include "helper.h"

var_cont* var_new(b_type type)
{
	var_cont* new = (var_cont*)malloc(sizeof(var_cont));
	ASSERT(new != NULL, "Could not allocate memory\n");

	new->type = type;
	new->data = NULL;
	return new;
}

void var_del(var_cont* var)
{
	if (var == NULL)
		return;
	
	if (var->data != NULL)
		free(var->data);

	free(var);
}
