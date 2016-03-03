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

	int idata;

	var_set(var, var_data_alloc_G_INT(42), G_INT);

	idata = var_data_get_G_INT(var);

	printf("key2 value: %i\n", idata);

	var_set(var, var_data_alloc_G_INT(32), G_INT);

	idata = var_data_get_G_INT(var);

	printf("key2 value: %i\n", idata);

	double ddata;

	var_cont* var1 = ht_get(hashtable, "key3");

	var_set(var1, var_data_alloc_G_FLOAT(3.1416), G_FLOAT);

	ddata = var_data_get_G_FLOAT(var1);

	printf("key3 value: %f\n", ddata);

	ht_destroy(hashtable);

	return 0;
}
