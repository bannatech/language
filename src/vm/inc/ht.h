/* `ht` Hashtable implementation
 */

#ifndef HT_H
#define HT_H

#include <stdlib.h>

#include "types.h"

typedef struct ht_entry {
	char* key;
	var_cont* value;
	struct ht_entry *next;
} ht_entry;

typedef struct ht_t {
	int size;
	ht_entry** table;
} ht_t;

/* Creates hashtable of size
 */
ht_t* ht_create(int);

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
