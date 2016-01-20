#include <stdio.h>

#include "ht.h"

int main(int argc, char* argv[])
{
	ht_t* hashtable = ht_init(65536);
	ht_set(hashtable, "key1", var_new(0));
	ht_set(hashtable, "key2", var_new(1));
	ht_set(hashtable, "key3", var_new(2));

	printf("%i\n", ht_get(hashtable, "key1")->type);
	printf("%i\n", ht_get(hashtable, "key2")->type);
	printf("%i\n", ht_get(hashtable, "key3")->type);

	ht_destroy(hashtable);
	return 0;
}
