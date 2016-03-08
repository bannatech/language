/*  var.h -> Provide implemenation of types
 */

#ifndef VAR_H
#define VAR_H

#include <stdlib.h>
#include <stdio.h>

#include "helper.h"

typedef unsigned int bc_addr;
typedef unsigned int ns_addr;

typedef enum {
	VOID,   // 0
	ADDR,   // 1
	TYPE,   // 2
	PLIST,  // 3
	FUNC,   // 4
	OBJECT, // 5
	G_INT,  // 6
	G_FLOAT,// 7
	G_CHAR, // 8
	G_STR,  // 9
	S_ARRAY,// A
	D_ARRAY,// B
	K_ARRAY,// C
	G_FIFO  // D
} b_type;

typedef struct var_cont {
	b_type type;
	void*  data;
} var_cont;

typedef struct var_data_type {
	b_type v;
} var_data_type;

typedef struct var_data_func {
	bc_addr loc;
	bc_addr end;
	b_type  type;
	ns_addr size;
	b_type* param;
} var_data_func;

typedef struct var_data_int {
	int v;
} var_data_int;

typedef struct var_data_float {
	double v;
} var_data_float;

typedef struct var_data_char {
	char v;
} var_data_char;

typedef struct var_data_str {
	size_t size;
	char* v;
} var_data_str;

typedef struct var_data_plist {
	b_type* v;
} var_data_plist;

#include "bc.h"

/* Initialze variable with type
 */
var_cont* var_new(b_type);

void* var_data_alloc_TYPE(b_type);
void* var_data_alloc_FUNC(b_type);
void* var_data_alloc_G_INT(int);
void* var_data_alloc_G_FLOAT(double);
void* var_data_alloc_G_CHAR(char);
void* var_data_alloc_G_STR(size_t);
void* var_data_alloc_PLIST(size_t);

/* Frees variable
 */
void var_del(var_cont*);
void var_data_free(void*, b_type);

void var_data_free_FUNC(void*);
void var_data_free_G_STR(void*);
void var_data_free_PLIST(void*);

/* Sets variable
 * void* -> pointer to allocated space of memory that agrees with b_type
 */
void var_set(var_cont*, void*, b_type);

b_type         var_data_get_TYPE(var_cont*);
var_data_func* var_data_get_FUNC(var_cont*);
int            var_data_get_G_INT(var_cont*);
double         var_data_get_G_FLOAT(var_cont*);
char           var_data_get_G_CHAR(var_cont*);
char*          var_data_get_G_STR(var_cont*);
b_type*        var_data_get_PLIST(var_cont*);


void* var_data_cpy_G_INT(var_data_int*);
void* var_data_cpy_G_FLOAT(var_data_float*);
void* var_data_cpy_G_CHAR(var_data_char*);
void* var_data_cpy_G_STR(var_data_str*);

var_cont* var_data_cpy(var_cont*);

/* Lovely little function to take bytes and turn it into an integer.
 *  int     - sizeof(bytes)
 *  byte_t* - array of bytes
 */
var_cont* bytes_to_int(int, byte_t*);

/* Byte to b_type.
 *  byte_t - value maps to enum b_type
 */
var_cont* byte_to_type(byte_t);

/* Converts array of bytes of size n into parameter list
 *
 *  int     - sizeof(bytes)
 *  byte_t* - array of bytes
 */
var_cont* raw_to_plist(int, byte_t*);
/* Raw variable to var_cont
 *
 *  int     - sizeof(bytes)
 *  byte_t* - array of bytes
 */
var_cont* raw_to_var(int, byte_t*);

#endif // var_H
