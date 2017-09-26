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

void playstk(stk_t* new)
{
	var_cont* one = var_new(VOID);
	var_cont* two = var_new(G_INT);
	var_cont* three = var_new(G_FLOAT);
	var_cont* four = var_new(G_CHAR);
	var_cont* five = var_new(G_STR);

	stk_push(new, one);
	stk_push(new, two);
	stk_push(new, three);
	stk_push(new, four);
	stk_push(new, five);

	printf("init: \n");
	printstk(new);

	stk_pop(new);

	printf("stk_pop: \n");
	printstk(new);

	stk_rot_top(new);

	printf("stk_rot_top: \n");
	printstk(new);

	stk_rot_top(new);

	stk_rot_three(new);

	printf("stk_rot_top + stk_rot_three: \n");
	printstk(new);

	stk_rot_three(new);

	printf("stk_rot_three: \n");
	printstk(new);
}

int main(int argc, char* argv[])
{
	init_var_track();

	stk_t* new = stk_new();

	playstk(new);

	printf("-- NEW STACK LEVEL --\n");
	stk_newlevel(&new);

	playstk(new);

	printf("-- LEVEL 1: ");
	printstk(new);

	stk_poplevel(&new);

	printf("-- LEVEL 0: ");
	printstk(new);

	stk_newlevel(&new);
	stk_newlevel(&new);

	stk_del(new);

	return 0;
}
