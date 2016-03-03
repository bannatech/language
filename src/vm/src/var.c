#include <stdlib.h>
#include <stdio.h>

#include "var.h"
#include "helper.h"

void* var_data_alloc_G_INT(int value)
{
	var_data_int* rv = (var_data_int*)malloc(sizeof(var_data_int));
	M_ASSERT(rv);

	rv->v = value;

	return rv;
}

void* var_data_alloc_G_FLOAT(double value)
{
	var_data_float* rv = (var_data_float*)malloc(sizeof(var_data_float));
	M_ASSERT(rv);

	rv->v = value;

	return (void**)rv;
}

void* var_data_alloc_G_CHAR(char value)
{
	var_data_char* rv = (var_data_char*)malloc(sizeof(var_data_char));
	M_ASSERT(rv);

	rv->v = value;

	return rv;
}

void* var_data_alloc_G_STR(size_t size)
{
	var_data_str* rv = (var_data_str*)malloc(sizeof(var_data_str));
	M_ASSERT(rv);

	rv->v = (char*)malloc(sizeof(char)*size);

	return rv;
}

void* var_data_alloc(b_type type)
{
	void* rv = NULL;

	if (type ==  G_INT)
		rv = var_data_alloc_G_INT(0);

	if (type ==  G_FLOAT)
		rv = var_data_alloc_G_FLOAT(0.0);

	if (type ==  G_CHAR)
		rv = var_data_alloc_G_CHAR(0);

	if (type ==  G_STR)
	{
		rv = var_data_alloc_G_STR(1);
	}

	return rv;
}

var_cont* var_new(b_type type)
{
	var_cont* new = (var_cont*)malloc(sizeof(var_cont));
	M_ASSERT(new);

	new->type = type;

	new->data = NULL;

	return new;
}

void var_data_free(void* data, b_type type)
{
	N_ASSERT(data);

	if (type == G_INT)
		free(data);

	if (type == G_FLOAT)
		free(data);

	if (type == G_CHAR)
		free(data);

	if (type == G_STR)
	{
		var_data_str* d = data;
		if (d->v != NULL)
			free(d->v);

		free(data);
	}
}

void var_del(var_cont* var)
{
	N_ASSERT(var);

	if (var->data != NULL)
		var_data_free(var->data, var->type);

	free(var);
}

void var_set(var_cont* var, void* data, b_type type)
{
	if (var == NULL || data == NULL)
		return;

	ASSERT(var->type == type,
		"Trying to set variable of different type without cast\n");
	
	if (var->data != NULL)
		var_data_free(var->data, type);
	
	var->data = data;
}

int var_data_get_G_INT(var_cont* var)
{
	N_ASSERT(var);
	ASSERT( var->type == G_INT, "TypeError" );

	N_ASSERT(var->data);

	var_data_int* t = var->data;

	return t->v;
}

double var_data_get_G_FLOAT(var_cont* var)
{
	N_ASSERT(var);
	ASSERT( var->type == G_FLOAT, "TypeError" );

	N_ASSERT(var->data);

	var_data_float* t = var->data;

	return t->v;
}

char var_data_get_G_CHAR(var_cont* var)
{
	N_ASSERT(var);
	ASSERT( var->type == G_CHAR, "TypeError" );

	N_ASSERT(var->data);

	var_data_char* t = var->data;

	return t->v;
}

char* var_data_get_G_STR(var_cont* var)
{
	N_ASSERT(var);
	ASSERT( var->type == G_STR, "TypeError" );

	N_ASSERT(var->data);

	var_data_str* t = var->data;

	return t->v;
}
