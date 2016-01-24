#include <stdio.h>

#include "var.h"

int main( void )
{
	var_cont* test0 = var_new(VOID);
	if (test0->type == VOID)
		printf("1\n");
	else
		printf("0\n");
	
	var_cont* test1 = var_new(G_INT);

	var_set(test1, var_data_alloc_G_INT(32), G_INT);
	int testing = *(test1->data);
	if (testing == 32)
		printf("1\n");
	else
		printf("0: %d\n", testing);

	var_del(test0);
	var_del(test1);
}
