#include <stdlib.h>
#include <stdio.h>

#include "var.h"

#include "bc.h"
#include "helper.h"

void* var_data_alloc_TYPE(b_type type)
{
	var_data_type* rv = (var_data_type*)malloc(sizeof(var_data_type));
	M_ASSERT(rv);

	rv->v = type;

	return rv;
}

void* var_data_alloc_FUNC(b_type type)
{
	var_data_func* rv = (var_data_func*)malloc(sizeof(var_data_func));
	M_ASSERT(rv);

	rv->type  = type;
	rv->loc   = 0;
	rv->end   = 0;
	rv->size  = 0;
	rv->param = NULL;

	return rv;
}

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

	return rv;
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

void* var_data_alloc_PLIST(size_t size)
{
	var_data_plist* rv = (var_data_plist*)malloc(sizeof(var_data_plist));
	M_ASSERT(rv);

	rv->v = (b_type*)malloc(sizeof(b_type)*size);

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

void var_del(var_cont* var)
{
	N_ASSERT(var);

	if (var->data != NULL)
		var_data_free(var->data, var->type);

	free(var);
}

void var_data_free(void* data, b_type type)
{
	N_ASSERT(data);

	if (type == FUNC)
	{
		var_data_free_FUNC(data);
	}

	if (type == G_STR)
	{
		var_data_free_G_STR(data);
	}

	if (type == PLIST)
	{
		var_data_free_PLIST(data);
	}

	if (data != NULL)
		free(data);
}

void var_data_free_FUNC(void* data)
{
	var_data_func* d = data;
	if (d->param != NULL)
		free(d->param);
}

void var_data_free_G_STR(void* data)
{
	var_data_str* d = data;
	if (d->v != NULL)
		free(d->v);
}
void var_data_free_PLIST(void* data)
{
	var_data_plist* d = data;
	if (d->v != NULL)
		free(d->v);
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

b_type var_data_get_TYPE(var_cont* var)
{
	N_ASSERT(var);
	ASSERT( var->type == TYPE, "TypeError" );

	var_data_type* t = var->data;

	return t->v;
}

var_data_func* var_data_get_FUNC(var_cont* var)
{
	N_ASSERT(var);
	ASSERT( var->type == FUNC, "TypeError" );

	var_data_func* t = var->data;

	return t;
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

b_type* var_data_get_PLIST(var_cont* var)
{
	N_ASSERT(var);
	ASSERT( var->type == PLIST, "TypeError" );

	N_ASSERT(var->data);

	var_data_plist* t = var->data;

	return t->v;
}

/* Lovely little function to take bytes and turn it into an integer.
 *  int     - sizeof(bytes)
 *  byte_t* - array of bytes
 */
void bytes_to_int(var_cont** rv, int size, byte_t* bytes)
{
	*rv = var_new(G_INT);

	int i,
	    data;

	data = 0;
	for ( i = 0; i < size; i++)
	{
		data = (data << 8 | bytes[i]);
	}

	var_set(*rv, var_data_alloc_G_INT(data), G_INT);
}

void byte_to_type(var_cont** rv, byte_t byte)
{
	*rv = var_new(TYPE);

	var_set(*rv, var_data_alloc_TYPE((b_type)byte), TYPE);
}

/* Converts array of bytes of size n into parameter list
 *
 *  int     - sizeof(bytes)
 *  byte_t* - array of bytes
 */
void raw_to_plist(var_cont** rv, int n, byte_t* bytes)
{
	*rv = var_new(PLIST);

	var_set(*rv, var_data_alloc_PLIST(n), PLIST);

	b_type* var = var_data_get_PLIST(*rv);

	int i;

	for (i = 0; i < n; i++)
	{
		var[i] = (b_type)bytes[i];
	}
}

/* Raw variable to var_cont
 *
 *  int     - sizeof(bytes)
 *  byte_t* - array of bytes
 */
void raw_to_var(var_cont** rv, int n, byte_t* bytes)
{
	*rv = var_new(VOID);

	// TODO: implement.
}

