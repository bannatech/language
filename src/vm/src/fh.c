#include <stdio.h>
#include <stdlib.h>

#include "fh.h"

byte_t* read_until_null(FILE* f)
{
	long f_pos_i = ftell(f);
	
	// This bit needs to be refactored.
	byte_t byte = read_byte(f);
	while (byte != 0)
	{
		byte = read_byte(f);
	}

	long bytes = (ftell(f) - f_pos_i);

	fseek(f, 0-bytes, SEEK_CUR);

	return read_bytes(f, bytes);
}

byte_t* read_bytes(FILE* f, long bytes)
{
	byte_t* buffer = (byte_t*)malloc(bytes*sizeof(byte_t));
	if (buffer == NULL)
		return buffer;

	fread(buffer, bytes, 1, f);

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
