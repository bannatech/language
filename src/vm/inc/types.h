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
	G_STRING,
	S_ARRAY,
	D_ARRAY,
	K_ARRAY,
	G_FIFO
} b_type;

typedef struct var_cont {
	b_type type;
	void* data;
} var_cont;

typedef void var_data_void;

typedef int var_data_int;

typedef char var_data_char;

typedef struct var_data_str {
	char* str;
} var_data_str;

/* Initialze variable with type
 */
var_cont* var_new(b_type);

/* Frees variable
 */
void var_del(var_cont*);

#endif // TYPES_H
