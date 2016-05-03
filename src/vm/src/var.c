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

void* var_data_alloc_PLIST(size_t size)
{
	var_data_plist* rv = (var_data_plist*)malloc(sizeof(var_data_plist));
	M_ASSERT(rv);

	rv->v = (b_type*)malloc(sizeof(b_type)*size);

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

void* var_data_alloc_OBJBLDR(void)
{
	var_data_objbldr* rv = (var_data_objbldr*)malloc(sizeof(var_data_objbldr));
	M_ASSERT(rv);

	rv->id    = 0;
	rv->loc   = 0;
	rv->end   = 0;
	rv->size  = 0;
	rv->instc = 0;
	rv->param = NULL;

	return rv;
}

void* var_data_alloc_OBJECT(void (*freefunc)(void*))
{
	N_ASSERT(freefunc, "var_data_alloc_OBJECT\n");

	var_data_object* rv = (var_data_object*)malloc(sizeof(var_data_object));
	M_ASSERT(rv);

	rv->id      = 0;
	rv->ref     = NULL;
	rv->objfree = freefunc;

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

	rv->size = size;
	rv->v = (char*)malloc(sizeof(char)*size);

	return rv;
}

var_cont* var_new(b_type type)
{
	var_cont* new = (var_cont*)malloc(sizeof(var_cont));
	M_ASSERT(new);

	new->ownership = -1;

	new->type = type;

	new->data = NULL;

	return new;
}

void var_del(var_cont* var)
{
	if (var != NULL)
	{
		if (var->data != NULL)
			var_data_free(var->data, var->type);

		free(var);
	}
}

void var_data_free(void* data, b_type type)
{
	N_ASSERT(data, "var_data_free\n");

	if (type == FUNC)
	{
		var_data_free_FUNC(data);
	}

	if (type == OBJBLDR)
	{
		var_data_free_OBJBLDR(data);
	}

	if (type == OBJECT)
	{
		var_data_free_OBJECT(data);
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

void var_data_free_PLIST(void* data)
{
	var_data_plist* d = data;
	if (d->v != NULL)
		free(d->v);
}
void var_data_free_FUNC(void* data)
{
	var_data_func* d = data;
	if (d->param != NULL)
		free(d->param);
}
void var_data_free_OBJBLDR(void* data)
{
	var_data_objbldr* d = data;
	if (d->param != NULL)
		free(d->param);
}
void var_data_free_OBJECT(void* data)
{
	var_data_object* d = data;
	if (d->ref != NULL)
		d->objfree(d->ref);
}
void var_data_free_G_STR(void* data)
{
	var_data_str* d = data;
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
	N_ASSERT(var, "var_data_get_TYPE\n");
	ASSERT( var->type == TYPE, "TypeError" );

	var_data_type* t = var->data;

	return t->v;
}

b_type* var_data_get_PLIST(var_cont* var)
{
	N_ASSERT(var, "var_data_get_PLIST\n");
	ASSERT( var->type == PLIST, "TypeError" );

	N_ASSERT(var->data, "var_data_get_PLIST\n");

	var_data_plist* t = var->data;

	return t->v;
}

var_data_func* var_data_get_FUNC(var_cont* var)
{
	N_ASSERT(var, "var_data_get_FUNC\n");
	ASSERT( var->type == FUNC, "TypeError" );

	var_data_func* t = var->data;

	return t;
}

var_data_objbldr* var_data_get_OBJBLDR(var_cont* var)
{
	N_ASSERT(var, "var_data_get_OBJBLDR\n");
	ASSERT( var->type == OBJBLDR, "TypeError" );

	var_data_objbldr* t = var->data;

	return t;
}

var_data_object* var_data_get_OBJECT(var_cont* var)
{
	N_ASSERT(var, "var_data_get_OBJECT\n");
	ASSERT( var->type == OBJECT, "TypeError" );

	var_data_object* t = var->data;
	
	return t;
}

int var_data_get_G_INT(var_cont* var)
{
	N_ASSERT(var, "var_data_get_G_INT\n");
	ASSERT( var->type == G_INT, "TypeError" );

	N_ASSERT(var->data, "var_data_get_G_INT\n");

	var_data_int* t = var->data;

	return t->v;
}

double var_data_get_G_FLOAT(var_cont* var)
{
	N_ASSERT(var, "var_data_get_G_FLOAT\n");
	ASSERT( var->type == G_FLOAT, "TypeError" );

	N_ASSERT(var->data, "var_data_get_G_FLOAT\n");

	var_data_float* t = var->data;

	return t->v;
}

char var_data_get_G_CHAR(var_cont* var)
{
	N_ASSERT(var, "var_data_get_G_CHAR\n");
	ASSERT( var->type == G_CHAR, "TypeError" );

	N_ASSERT(var->data, "var_data_get_G_CHAR\n");

	var_data_char* t = var->data;

	return t->v;
}

char* var_data_get_G_STR(var_cont* var)
{
	N_ASSERT(var, "var_data_get_G_STR\n");
	ASSERT( var->type == G_STR, "TypeError" );

	N_ASSERT(var->data, "var_data_get_G_STR\n");

	var_data_str* t = var->data;

	return t->v;
}

void* var_data_cpy_G_INT(var_data_int* data)
{
	var_data_int* rv = var_data_alloc_G_INT(data->v);

	return rv;
}

void* var_data_cpy_G_FLOAT(var_data_float* data)
{
	var_data_float* rv = var_data_alloc_G_FLOAT(data->v);

	return rv;
}

void* var_data_cpy_G_CHAR(var_data_char* data)
{
	var_data_char* rv = var_data_alloc_G_CHAR(data->v);

	return rv;
}

void* var_data_cpy_G_STR(var_data_str* data)
{
	var_data_str* rv = var_data_alloc_G_STR(data->size);

	int i;
	for (i = 0; data->size > i; i++)
	{
		rv->v[i] = data->v[i];
	}

	return rv;
}

/* Reconstructs variable into seperate variable container, copies data
 *  var_cont* - variable to copy
 *
 * Returns new variable container
 */
var_cont* var_data_cpy(var_cont* var)
{
	N_ASSERT(var, "var_data_cpy\n");

	var_cont* rv = var_new(var->type);

	if (var->type == G_INT)
	{
		rv->data = var_data_cpy_G_INT(var->data);
	}
	
	if (var->type == G_FLOAT)
	{
		rv->data = var_data_cpy_G_FLOAT(var->data);
	}

	if (var->type == G_CHAR)
	{
		rv->data = var_data_cpy_G_CHAR(var->data);
	}
	
	if (var->type == G_STR)
	{
		rv->data = var_data_cpy_G_STR(var->data);
	}

	if (var->type == OBJECT)
	{
		rv->data = var->data;
	}

	ASSERT((rv->data != NULL), "ERROR: Could not copy type.\n");

	return rv;
}

/* Lovely little function to take bytes and turn it into an integer.
 *  int     - sizeof(bytes)
 *  byte_t* - array of bytes
 */
var_cont* raw_to_int(int size, int start, byte_t* bytes)
{
	var_cont* rv = var_new(G_INT);

	int i,
	    data;
	data = 0;
	for ( i = start; i < size; i++)
	{
		data = (data << 8 | bytes[i]);
	}

	var_set(rv, var_data_alloc_G_INT(data), G_INT);

	return rv;
}

/* Byte to b_type.
 *  byte_t - value maps to enum b_type
 */
var_cont* byte_to_type(byte_t byte)
{
	var_cont* rv = var_new(TYPE);

	var_set(rv, var_data_alloc_TYPE((b_type)byte), TYPE);

	return rv;
}

/* Converts array of bytes of size n into parameter list
 *
 *  int     - sizeof(bytes)
 *  byte_t* - array of bytes
 */
var_cont* raw_to_plist(int n, byte_t* bytes)
{
	var_cont* rv = var_new(PLIST);

	var_set(rv, var_data_alloc_PLIST(n), PLIST);

	b_type* var = var_data_get_PLIST(rv);

	int i;

	for (i = 0; i < n; i++)
	{
		var[i] = (b_type)bytes[i];
	}

	return rv;
}

/* Converts raw (ascii) string into normal string type
 * int     - sizeof(bytes)
 * int     - offset
 * byte_t* - array of bytes
 */
var_cont* raw_to_str(int n, int offset, byte_t* bytes)
{
	var_cont* rv = var_new(G_STR);
	var_data_str* data = var_data_alloc_G_STR(n);
	int i;
	for (i = offset; n > i; i++)
	{
		data->v[i] = (char)bytes[i];
	}

	var_set(rv, data, G_STR);

	return rv;
}

/* Raw variable to var_cont
 *
 *  int     - sizeof(bytes)
 *  byte_t* - array of bytes
 */
var_cont* raw_to_var(int n, byte_t* bytes)
{
	N_ASSERT(bytes, "raw_to_var\n");

	b_type type = (b_type)bytes[0];

	var_cont* rv;

	if (type == G_INT)
	{
		rv = raw_to_int(n, 1, bytes);
	} else
	if (type == G_STR)
	{
		rv = raw_to_str(n, 1, bytes);
	} else
	{
		printf("Type {%x} is not a seralizeable type\n", type);
	}

	N_ASSERT(rv, "raw_to_var");

	return rv;
}

