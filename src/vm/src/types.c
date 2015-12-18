#include <stdlib.h>
#include <stdio.h>

#include "types.h"

var_cont* var_new(b_type type)
{
	var_cont* new = (var_cont*)malloc(sizeof(var_cont));
	if (new == NULL)
	{
		fprintf(stderr, "Could not allocate memory");
		exit(1);
	}
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
