#include <stdio.h>
#include <stdlib.h>

#include "fh.h"
#include "helper.h"

byte_t* read_bytes(FILE* f, long bytes)
{
	byte_t* buffer = (byte_t*)malloc(bytes*sizeof(byte_t));

	ASSERT(buffer != NULL, "Could not allocate memory\n");

	fread(buffer, bytes, sizeof(byte_t), f);

	return buffer;
}

byte_t read_byte(FILE* f)
{
	return fgetc(f);
}

long read_size(FILE* f)
{
	fseek(f, 0, SEEK_END);

	long fsize = 0;
	fsize = ftell(f);
	rewind(f);

	return fsize;
}
