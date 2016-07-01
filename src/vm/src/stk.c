#include <stdlib.h>
#include <stdio.h>

#include "stk.h"
#include "var.h"
#include "helper.h"

stk_t* stk_new( void )
{
	stk_t* new = (stk_t*)malloc(sizeof(stk_t));
	M_ASSERT(new);

	new->stack = stk_line_new(STACK_INIT_SIZE);
	new->next  = NULL;

	return new;
}

stk_line* stk_line_new(size_t size)
{
	ASSERT(size > 1, "stk_line_new\n");

	stk_line* new = (stk_line*)malloc(sizeof(stk_line));
	M_ASSERT(new);

	new->data = (var_cont**)malloc(sizeof(var_cont*)*size);
	M_ASSERT(new);

	int i;
	for (i = 0; i < size; i++)
	{
		new->data[i] = NULL;
	}

	new->size = size;
	new->ptr  = 0;

	return new;
}

void stk_del(stk_t* stack)
{
	N_ASSERT(stack, "stk_del");

	while (stack->next != NULL)
	{
		stk_poplevel(&stack);
	}

	free(stack);
}

void stk_line_del(stk_line* stack)
{
	N_ASSERT(stack, "stk_line_del\n");

	int i;
	for (i = 0; i < stack->size; i++)
	{
		if (stack->data[i] != NULL)
		{
			if (stack->data[i]->ownership < 0)
				var_del(stack->data[i]);
		}
	}

	free(stack->data);
	free(stack);
}

/* Pushes a new stack level
 *  stk_t** - stack instances
 */
void stk_newlevel(stk_t** stack)
{
	N_ASSERT(stack, "stk_newlevel\n");

	stk_t* new = stk_new();

	new->next = *stack;

	*stack = new;
}

/* Pops a stack level
 *  stk_t* - stack instance
 */
void stk_poplevel(stk_t** stack)
{
	N_ASSERT(stack, "stk_poplevel\n");

	if ((*stack)->next != NULL)
	{
		stk_t* tmp = (*stack)->next;
		stk_line_del((*stack)->stack);
		free(*stack);
		*stack = tmp;
	}
}

/* Scales the stack by n^2
 *  stk_t* - stack instance
 */
void stk_scale(stk_line* stack)
{
	N_ASSERT(stack, "stk_scale\n");

	size_t newsize = stack->size * stack->size;

	stack->data = realloc(stack->data, sizeof(var_cont*) * newsize);
}

/* Pop the first element of the stack
 *  stk_t* - stack instance
 */
var_cont* stk_pop(stk_t* stack)
{
	N_ASSERT(stack, "stk_pop\n");

	ASSERT(((stack->stack->ptr - 1) >= 0), "Stack Underflow\n");

	stack->stack->ptr = stack->stack->ptr - 1;

	var_cont* rv = stack->stack->data[stack->stack->ptr];

	stack->stack->data[stack->stack->ptr] = NULL;

	return rv;
}

/* Pushes var_cont* to the stack
 *  stk_t*     - stack instance
 *  var_cont*  - variable instance
 */
void stk_push(stk_t* stack, var_cont* data)
{
	N_ASSERT(stack, "stk_push\n");
	N_ASSERT(data, "stk_push\n");

	if ((stack->stack->ptr + 1) < stack->stack->size)
	{
		stk_scale(stack->stack);
	}

	stack->stack->data[stack->stack->ptr] = data;

	stack->stack->ptr = stack->stack->ptr + 1;
}

/* Returns the data at location in the stack
 *  stk_line* - Stack line instance
 *  int       - (integer + 1) < (STK_SIZE_LIMIT - stk_line->ptr)
 */
var_cont* stk_at(stk_t* stack, int n)
{
	n = n + 1;

	ASSERT(((stack->stack->ptr - n) >= 0), "Out of Bounds\n");

	var_cont* rv = stack->stack->data[stack->stack->ptr - n];

	return rv;
}

/* Rotates the top two elements of the stack
 * i.e. [4, 3, 2, 1] -> [3, 4, 2, 1]
 *                   ^ rot_top()
 */
void stk_rot_top(stk_t* stack)
{
	N_ASSERT(stack, "stk_rot_top\n");

	var_cont* a;
	var_cont* b;

	a = stk_pop(stack);
	b = stk_pop(stack);
	stk_push(stack, a);
	stk_push(stack, b);
}

/* Rotates the top three elements of the stack
 * i.e. [4, 3, 2, 1] -> [2, 3, 4, 1]
 *                   ^ rot_three()
 */
void stk_rot_three(stk_t* stack)
{
	N_ASSERT(stack, "stk_rot_three\n");

	var_cont* a;
	var_cont* b;
	var_cont* c;

	a = stk_pop(stack);
	b = stk_pop(stack);
	c = stk_pop(stack);
	stk_push(stack, a);
	stk_push(stack, b);
	stk_push(stack, c);
}
