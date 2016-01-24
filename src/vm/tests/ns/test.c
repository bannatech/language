#include <stdio.h>

#include "ns.h"

int main( void )
{
	ns_t* test = ns_init(10);

	ns_push(test, 5);

	ns_push(test, 2);

	printf("%d\n", test->last->size);

	ns_pop(test);
	
	printf("%d\n", test->last->size);

	ns_pop(test);

	printf("%d\n", test->last->size);

	ns_del(test);

	return 0;
}
