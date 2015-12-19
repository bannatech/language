#include <stdlib.h>

#include "ht.h"
#include "types.h"
#include "helper.h"

ht_t* ht_init(int size)
{
	ht_t* hashtable = (ht_t*)malloc(sizeof(ht_t));
	ASSERT(hashtable != NULL, "Could not allocate memory\n");

	hashtable->size = size;

	hashtable->table = ht_init_table(hashtable->size);

	return hashtable;
}

ht_entry** ht_init_table(int size)
{
	ht_entry** table = (ht_entry**)malloc(sizeof(ht_entry)*size);
	ASSERT(table != NULL, "Could not allocate memory\n");

	for (int i = 0; i < size; i++)
	{
		table[i]->key = NULL;
		table[i]->value = var_new(0);
		table[i]->next = NULL;
	}

	return table;
}

void ht_destroy(ht_t* hashtable)
{
	ht_destroy_table(hashtable->table, hashtable->size);
}

void ht_destroy_table(ht_entry** table, int size)
{
	for (int i = 0; i < size; i++)
	{
		ht_destroy_entry(table[i]);
	}
}

void ht_destroy_entry(ht_entry* entry)
{
	var_del(entry->value);

	if (entry->key != NULL)
		free(entry->key);

	if (entry->next != NULL)
		ht_destroy_entry(entry->next);
	
	free(entry);
}

