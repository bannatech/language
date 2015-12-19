/* stk.h -> Provide implementation of a stack
 */

#ifndef STK_H
#define STK_H

#include <stdlib.h>
#include <stdio.h>

#include "types.h"
#include "helper.h"

typedef struct stk_t {
	struct stk_t* next;
	var_cont* data;
} stk_t;

/* Create a new stack instance
 */
stk_t* stk_new(void);

/* Delete a stack
 */
void stk_del(stk_t*);

/* Pop the first element of the stack
 *
 * @param stk_t*
 *  stack instance pointer
 */
var_cont* stk_pop(stk_t**);

/* Pushes @param var_cont* to the stack
 */
void stk_push(stk_t**, var_cont*);

/* Returns the data at location in the stack
 */
var_cont* stk_at(stk_t*, int);

/* Rotates the top two elements of the stack
 * i.e. [4, 3, 2, 1] -> [3, 4, 2, 1]
 *                   ^ rot_top()
 */
void stk_rot_top(stk_t**);

/* Rotates the top three elements of the stack
 * i.e. [4, 3, 2, 1] -> [2, 3, 4, 1]
 *                   ^ rot_three()
 */
void stk_rot_three(stk_t**);

#endif // STK_H
