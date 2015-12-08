/*
 'fh.h' is here to provide useful functions to mess about with files.
*/

#ifndef FH_H
#define FH_H

#include <stdio.h>
#include <stdlib.h>

typedef unsigned char byte_t;

byte_t* read_until_null(FILE*);

byte_t* read_bytes(FILE*, long);

byte_t read_byte(FILE*);

long read_size(FILE*);

#endif // FH_H
