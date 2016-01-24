#include <stdlib.h>
#include <stdio.h>

#include "var.h"
#include "helper.h"

void** var_data_alloc_G_INT(var_data_int value)
{
	var_data_int* rv = (var_data_int*)malloc(sizeof(var_data_int));
	M_ASSERT(rv);

	*rv = value;

	return (void**)rv;
}

void** var_data_alloc_G_FLOAT(var_data_float value)
{
	var_data_float* rv = (var_data_float*)malloc(sizeof(var_data_float));
	M_ASSERT(rv);

	*rv = value;

	return (void**)rv;
}

void** var_data_alloc_G_CHAR(var_data_char value)
{
	var_data_char* rv = (var_data_char*)malloc(sizeof(var_data_char));
	M_ASSERT(rv);

	*rv = value;

	return (void**)rv;
}

void** var_data_alloc_G_STR(size_t size)
{
	var_data_str* rv = (var_data_str*)malloc(sizeof(var_data_str));
	M_ASSERT(rv);

	rv->str = (var_data_char*)malloc(sizeof(var_data_char)*size);

	return (void**)rv;
}

void** var_data_alloc(b_type type)
{
	void** rv = NULL;

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

	new->data = var_data_alloc(type);

	return new;
}

void var_data_free(void** data, b_type type)
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
		var_data_str* t_data = *data;
		if (t_data->str != NULL)
			free(t_data->str);

		free(data);
	}
}

void var_del(var_cont* var)
{
	if (var == NULL)
		return;

	if (var->data != NULL)
		var_data_free(var->data, var->type);

	free(var);
}

void var_set(var_cont* var, void** data, b_type type)
{
	if (var == NULL || data == NULL)
		return;

	ASSERT(var->type == type,
		"Trying to set variable of different type without cast\n");
	
	if (var->data != NULL)
		var_data_free(var->data, type);
	
	var->data = data;
}

void** var_cast_data_G_INT(void** data, b_type type)
{
	N_ASSERT(data);

	free(data);

	return var_data_alloc(type);
}

void** var_cast_data_G_FLOAT(void** data, b_type type)
{
	N_ASSERT(data);

	free(data);

	return var_data_alloc(type);
}

void** var_cast_data_G_CHAR(void** data, b_type type)
{
	N_ASSERT(data);

	free(data);

	return var_data_alloc(type);
}

void** var_cast_data_G_STR(void** data, b_type type)
{
	N_ASSERT(data);

	free(data);

	return var_data_alloc(type);
}

void** var_cast_data(var_cont* var, b_type type)
{
	void** rv = NULL;

	if (var->type == G_INT)
		rv = var_cast_data_G_INT(var->data, type);

	if (var->type == G_FLOAT)
		rv = var_cast_data_G_FLOAT(var->data, type);

	if (var->type == G_CHAR)
		rv = var_cast_data_G_CHAR(var->data, type);

	if (var->type == G_STR)
		rv = var_cast_data_G_STR(var->data, type);

	return rv;
}

void var_cast(var_cont* var, b_type type)
{
	if (var == NULL)
		return;
	
	if (var->data == NULL)
		return;

	var->data = var_cast_data(var, type);

	var->type = type;
}

