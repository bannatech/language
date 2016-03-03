/*  types.h -> Provide implemenation of types
 */

#ifndef TYPES_H
#define TYPES_H

#include <stdlib.h>
#include <stdio.h>

#include "helper.h"

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
	void* data;
} var_cont;

typedef struct var_data_void {
	void* v;
} var_data_void;

typedef struct var_data_int {
	int v;
} var_data_int;

typedef struct var_data_float {
	double v;
} var_data_float;

typedef struct var_data_char {
	char v;
} var_data_char;
/*
typedef char var_data_u_char;
*/
typedef struct var_data_str {
	char* v;
} var_data_str;
/*
typedef struct var_data_u_str {
	var_data_u_char* str;
} var_data_u_str;
*/

/* Initialze variable with type
 */
var_cont* var_new(b_type);

void* var_data_alloc(b_type);
void* var_data_alloc_G_INT(int);
void* var_data_alloc_G_FLOAT(double);
void* var_data_alloc_G_CHAR(char);
void* var_data_alloc_G_STR(size_t);

/* Frees variable
 */
void var_del(var_cont*);
void var_data_free(void*, b_type);

/* Sets variable
 * void** -> pointer to allocated space of memory that agrees with b_type
 */
void var_set(var_cont*, void*, b_type);

int    var_data_get_G_INT(var_cont*);
double var_data_get_G_FLOAT(var_cont*);
char   var_data_get_G_CHAR(var_cont*);
char*  var_data_get_G_STR(var_cont*);

#endif // TYPES_H
