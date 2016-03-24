/* stk.h -> Provide implementation of a stack
 */

#ifndef STK_H
#define STK_H

#define STACK_SIZE_LIMIT 0xFFFF
#define STACK_INIT_SIZE  0xFF

#include <stdlib.h>
#include <stdio.h>

#include "var.h"
#include "helper.h"

typedef struct stk_line {
	int        ptr;
	size_t     size;
	var_cont** data;
} stk_line;

typedef struct stk_t {
	struct stk_t* next;
	stk_line* stack;
} stk_t;

/* Create a new stack instance
 */
stk_t* stk_new(void);
stk_line* stk_line_new(size_t);

/* Delete a stack
 */
void stk_del(stk_t*);
void stk_line_del(stk_line*);

/* Pushes new stack level
 */
void stk_newlevel(stk_t**);

/* Pops a stack level
 */
void stk_poplevel(stk_t**);

/* Scales the stack by n^2
 *  stk_t* - stack instance
 */
void stk_scale(stk_line*);

/* Pop the first element of the stack
 *  stk_t* - stack instance
 */
var_cont* stk_pop(stk_t*);

/* Pushes var_cont* to the stack
 *  stk_t*     - stack instance
 *  var_cont*  - variable instance
 */
void stk_push(stk_t*, var_cont*);

/* Returns the data at location in the stack
 *  stk_line* - Stack line instance
 *  int       - integer < (STK_SIZE_LIMIT - stk_line->ptr)
 */
var_cont* stk_at(stk_t*, int);

/* Rotates the top two elements of the stack
 * i.e. [4, 3, 2, 1] -> [3, 4, 2, 1]
 *                   ^ rot_top()
 */
void stk_rot_top(stk_t*);

/* Rotates the top three elements of the stack
 * i.e. [4, 3, 2, 1] -> [2, 3, 4, 1]
 *                   ^ rot_three()
 */
void stk_rot_three(stk_t*);

#endif // STK_H
