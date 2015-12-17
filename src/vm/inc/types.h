/*
 * types.h -> Provide implemenation of types
 */

#include <stdlib.h>
#include <stdio.h>

#ifndef TYPES_H
#define TYPES_H

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
	A_ARRAY
} b_type;

typedef struct var_cont {
	b_type type;
	void* data;
} var_cont;

/*
 * Initialze variable with type
 */
var_cont* var_new(b_type);

/*
 * Frees variable
 */
void var_del(var_cont*);

#endif // TYPES_H
