#include <stdio.h>

#include "stk.h"
#include "var.h"


void printstk(stk_t* stk)
{
	var_cont* test0 = stk_at(stk, 0);
	var_cont* test1 = stk_at(stk, 1);
	var_cont* test2 = stk_at(stk, 2);
	var_cont* test3 = stk_at(stk, 3);
	printf("%i, %i, %i, %i\n",
	       test0->type, test1->type, test2->type, test3->type);
}

int main(int argc, char* argv[])
{
	stk_t* new = stk_new();
	new->data = var_new(0);

	stk_push(&new, var_new(1));
	stk_push(&new, var_new(2));
	stk_push(&new, var_new(3));
	stk_push(&new, var_new(4));
	stk_push(&new, var_new(5));

	printstk(new);

	stk_pop(&new);

	printstk(new);

	stk_rot_top(&new);

	printstk(new);

	stk_rot_top(&new);

	stk_rot_three(&new);

	printstk(new);

	stk_del(new);

	return 0;
}
