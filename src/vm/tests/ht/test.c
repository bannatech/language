#include <stdio.h>

#include "ht.h"

int main(int argc, char* argv[])
{
	ht_t* hashtable = ht_init(65536);
	ht_destroy(hashtable);
	return 0;
}
