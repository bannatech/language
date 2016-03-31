#include <stdio.h>
#include <stdlib.h>

#include "fh.h"
#include "helper.h"

/* Reads n bytes, n passed as @param long, returns array of byte_t
 */
byte_t* read_bytes(FILE* f, long bytes)
{
	byte_t* buffer = (byte_t*)malloc(bytes*sizeof(byte_t));

	ASSERT(buffer != NULL, "Could not allocate memory\n");

	fread(buffer, bytes, sizeof(byte_t), f);

	return buffer;
}

/* Reads a byte, returns byte_t
 */
byte_t read_byte(FILE* f)
{
	return fgetc(f);
}

/* Determines filesize, returns size as long
 */
long read_size(FILE* f)
{
	fseek(f, 0, SEEK_END);

	long fsize = 0;
	fsize = ftell(f);
	rewind(f);

	return fsize;
}
