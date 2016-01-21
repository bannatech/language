#define _XOPEN_SOUCE 500

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#include "ht.h"
#include "var.h"
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
	ht_entry** table = (ht_entry**)malloc(sizeof(ht_entry*)*size);
	ASSERT(table != NULL, "Could not allocate memory\n");

	for (int i = 0; i < size; i++)
	{
		table[i] = NULL;
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
		if (table[i] != NULL){
			ht_destroy_entry(table[i]);
		}
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

void ht_set(ht_t* hashtable, char* key, var_cont* value)
{
	int bucket = 0;
	ht_entry* np = NULL;
	ht_entry* next = NULL;
	ht_entry* last = NULL;

	bucket = ht_hash(hashtable, key);

	next = hashtable->table[ bucket ];

	/* Get relavent key/value pair if it exists in the bucket */
	while (next != NULL && next->key != NULL && strcmp(key, next->key) > 0)
	{
		last = next;
		next = next->next;
	}

	if (next != NULL && next->key != NULL && strcmp(key, next->key) == 0)
	{
		var_del(next->value);
		next->value = value;
	}
	else
	{
		np = ht_newpair(key, value);

		if (next == hashtable->table[bucket])
		{
			np->next = next;
			hashtable->table[bucket] = np;
		}
		else if (next == NULL)
		{
			last->next = np;
		}
		else
		{
			np->next = next;
			last->next = np;
		}
	}
}

var_cont* ht_get(ht_t* hashtable, char* key)
{
	int bucket = ht_hash(hashtable, key);

	ht_entry* pair = hashtable->table[bucket];
	while (pair != NULL && pair->key != NULL && strcmp(key, pair->key) > 0)
	{
		pair = pair->next;
	}

	if (pair == NULL || pair->key == NULL || strcmp(key, pair->key) != 0)
	{
		return var_new(0);
	}
	else
	{
		return pair->value;
	}
}

ht_entry* ht_newpair(char* key, var_cont* value)
{
	ht_entry* newpair;

	newpair = malloc(sizeof(ht_entry));
	ASSERT(newpair != NULL, "Couldn't allocate memory!");

	newpair->key = strdup(key);
	ASSERT(newpair->key != NULL, "Null keys are bad mhmkay");

	newpair->value = value;

	return newpair;
}

int ht_hash(ht_t* hashtable, char* key)
{
	unsigned long int hashval;
	int i = 0;

	/* Convert our string to an integer */
	while (hashval < ULONG_MAX && i < strlen(key))
	{
		hashval = hashval << 8;
		hashval += key[ i ];
		i++;
	}

	return hashval % hashtable->size;
}
