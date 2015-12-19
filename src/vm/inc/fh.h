/* 'fh.h' is here to provide useful functions to mess about with files.
 */

#ifndef FH_H
#define FH_H

#include <stdio.h>
#include <stdlib.h>

#include "helper.h"

typedef unsigned char byte_t;

/* Reads passed file descriptor until NULL, returns array of byte_t
 */
byte_t* read_until_null(FILE*);

/* Reads n bytes, n passed as @param long, returns array of byte_t
 */
byte_t* read_bytes(FILE*, long);

/* Reads a byte, returns byte_t
 */
byte_t read_byte(FILE*);

/* Determines filesize, returns size as long
 */
long read_size(FILE*);

#endif // FH_H
