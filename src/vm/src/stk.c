#include <stdlib.h>
#include <stdio.h>

#include "stk.h"
#include "var.h"
#include "helper.h"

stk_t* stk_new( void )
{
	stk_t* new = (stk_t*)malloc(sizeof(stk_t));
	ASSERT(new != NULL, "Could not allocate memory\n");

	return new;
}

void stk_del(stk_t* root)
{
	if (root->next != NULL)
	{
		stk_del(root->next);
	}

	if (root->data != NULL)
		var_del(root->data);

	free(root);
}

var_cont* stk_pop(stk_t** root)
{
	if ((*root)->next == NULL)
		return 0;

	stk_t* new = (*root)->next;
	var_cont* data = (*root)->data;

	free(*root);

	*root = new;

	return data;
}

void stk_push(stk_t** root, var_cont* data)
{
	stk_t* new = stk_new();
	new->data = data;
	new->next = *root;
	*root = new;
}

var_cont* stk_at(stk_t* root, int n)
{
	n--;
	if (n >= 0)
	{
		return stk_at(root->next, n);
	}
	else
	{
		return root->data;
	}
}

void stk_rot_top(stk_t** root)
{
	stk_t* tmp = (*root)->next;
	(*root)->next = tmp->next;
	tmp->next = *root;
	*root = tmp;
}

void stk_rot_three(stk_t** root)
{
	stk_t* tmp2 = (*root)->next->next;
	stk_t* tmp1 = (*root)->next;
	(*root)->next = tmp2->next;
	tmp2->next = tmp1;
	tmp1->next = *root;
	*root = tmp2;
}
