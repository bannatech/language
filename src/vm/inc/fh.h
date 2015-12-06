/*
 'fh.h' is here to provide useful functions to mess about with files.
*/

#ifndef FH_H
#define FH_H

#include <stdio.h>
#include <stdlib.h>

typedef unsigned char byte_t;

void read_until_null(FILE**, long*, byte_t**);

void read_bytes(FILE**, long*, int, byte_t**);

long read_size(FILE**, char*);

#endif // FH_H
