/* `ht` Hashtable implementation
 */

#ifndef HT_H
#define HT_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#include "types.h"
#include "helper.h"

typedef struct ht_entry {
	char* key;
	var_cont* value;
	struct ht_entry *next;
} ht_entry;

typedef struct ht_t {
	int size;
	ht_entry** table;
} ht_t;

/* Creates hashtable of @param int size
 */
ht_t* ht_init(int);

/* Creates the table of empty buckets for the hashtable
 */
ht_entry** ht_init_table(int);

/* Destroys hashtable
 */
void ht_destroy(ht_t*);

/* Destroys the table of buckets for the hashtable
 */
void ht_destroy_table(ht_entry**, int);

/* Destroys an entry.
 */
void ht_destroy_entry(ht_entry*);

/* Set a key-value pair
 */
void ht_set(ht_t*, char*, var_cont*);

/* Get a value
 */
var_cont* ht_get(ht_t*, char*);

/* Make a new key-value pair
 */
ht_entry* ht_newpair(char*, var_cont*);

/* Hash a string
 */
int ht_hash(ht_t*, char*);

#endif // HT_H
