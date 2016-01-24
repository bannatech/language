#include <stdio.h>

#include "var.h"
#include "ht.h"

int main(int argc, char* argv[])
{
	ht_t* hashtable = ht_init(2);
	ht_set(hashtable, "key1", var_new(VOID));
	ht_set(hashtable, "key2", var_new(G_INT));
	ht_set(hashtable, "key3", var_new(G_FLOAT));

	printf("%i\n", ht_get(hashtable, "key1")->type);
	printf("%i\n", ht_get(hashtable, "key2")->type);
	printf("%i\n", ht_get(hashtable, "key3")->type);

	var_cont* var = ht_get(hashtable, "key2");

	printf("key2 value: %i\n", *(var->data));

	var_set(var, var_data_alloc_G_INT(32), G_INT);

	printf("key2 value: %i\n", *(var->data));

	printf("key2 value: %i\n", *(ht_get(hashtable, "key2")->data));

	ht_destroy(hashtable);
	return 0;
}
