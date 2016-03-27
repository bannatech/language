#include <stdio.h>

#include "ns.h"

int main( void )
{
	ns_t* test = ns_init(10);

	var_cont* testing_on_namespace;
	var_cont* testing = var_new(G_INT);
	var_set(testing, var_data_alloc_G_INT(42), G_INT);

	printf("testing: %i, %i\n", testing->ownership,
	                            var_data_get_G_INT(testing));

	ns_dec(test, G_INT, 0, 2);
	ns_set(test, 0, 2, testing);

	testing_on_namespace = ns_get(test, 0, 2);
	printf("testing_on_namespace: %i, %i\n", testing_on_namespace->ownership,
	                                         var_data_get_G_INT(testing));

	ns_push(test, 5);

	var_cont* testing_2 = var_new(G_INT);
	var_set(testing_2, var_data_alloc_G_INT(24), G_INT);

	ns_dec(test, G_INT, 0, 1);
	ns_set(test, 0, 1, testing_2);

	testing_on_namespace = ns_get(test, 0, 1);
	printf("testing_on_namespace: %i, %i\n", testing_on_namespace->ownership,
	                                         var_data_get_G_INT(testing));

	ns_dec(test, G_INT, 0, 2);
	ns_set(test, 0, 2, testing);

	testing_on_namespace = ns_get(test, 0, 2);
	printf("testing_on_namespace: %i, %i\n", testing_on_namespace->ownership,
	                                         var_data_get_G_INT(testing));

	ns_push(test, 5);

	ns_dec(test, G_INT, 0, 2);
	ns_set(test, 0, 2, testing);

	testing_on_namespace = ns_get(test, 0, 2);
	printf("testing_on_namespace: %i, %i\n", testing_on_namespace->ownership,
	                                         var_data_get_G_INT(testing));

	printf("Namespace info: %d, %i\n", test->last->size, test->last->level);

	ns_pop(test);

	testing_on_namespace = ns_get(test, 0, 2);
	printf("testing_on_namespace: %i, %i\n", testing_on_namespace->ownership,
	                                         var_data_get_G_INT(testing));

	printf("Namespace info: %d, %i\n", test->last->size, test->last->level);

	ns_pop(test);

	testing_on_namespace = ns_get(test, 0, 2);
	printf("testing_on_namespace: %i, %i\n", testing_on_namespace->ownership,
	                                         var_data_get_G_INT(testing));

	printf("Namespace info: %d, %i\n", test->last->size, test->last->level);

	ns_del(test);

	return 0;
}
