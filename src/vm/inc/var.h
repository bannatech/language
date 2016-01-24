/*  types.h -> Provide implemenation of types
 */

#ifndef TYPES_H
#define TYPES_H

#include <stdlib.h>
#include <stdio.h>

typedef enum {
	VOID,
	FUNC,
	OBJECT,
	G_INT,
	G_FLOAT,
	G_CHAR,
	U_CHAR,
	G_STR,
	U_STR,
	S_ARRAY,
	D_ARRAY,
	K_ARRAY,
	G_FIFO
} b_type;

typedef struct var_cont {
	b_type type;
	void** data;
} var_cont;

typedef void var_data_void;

typedef int var_data_int;

typedef double var_data_float;

typedef char var_data_char;
/*
typedef char var_data_u_char;
*/
typedef struct var_data_str {
	var_data_char* str;
} var_data_str;
/*
typedef struct var_data_u_str {
	var_data_u_char* str;
} var_data_u_str;
*/

void** var_data_alloc_G_INT(var_data_int);
void** var_data_alloc_G_FLOAT(var_data_float);
void** var_data_alloc_G_CHAR(var_data_char);
void** var_data_alloc_G_STR(size_t);

void** var_data_alloc(b_type);

/* Initialze variable with type
 */
var_cont* var_new(b_type);

void var_data_free(void**, b_type);

/* Frees variable
 */
void var_del(var_cont*);

void var_set(var_cont*, void**, b_type);

var_cont* var_cast_data(var_cont*, b_type);

void var_cast(var_cont**, b_type);

var_cont* var_cast_data_G_INT(void**, b_type);
var_cont* var_cast_data_G_FLOAT(void**, b_type);
var_cont* var_cast_data_G_CHAR(void**, b_type);
var_cont* var_cast_data_G_STR(void**, b_type);

#endif // TYPES_H
