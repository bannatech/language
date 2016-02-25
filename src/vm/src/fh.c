#include <stdio.h>
#include <stdlib.h>

#include "fh.h"
#include "helper.h"

byte_t* read_until_null(FILE* f)
{
	long f_pos_i = ftell(f);

	// This bit gets the length in bytes it needs to read into a buffer
	byte_t byte = read_byte(f);
	while (byte != 0)
	{
		byte = read_byte(f);
	}

	long bytes = (ftell(f) - f_pos_i);

	// Seek backwards
	fseek(f, -bytes, SEEK_CUR);

	ASSERT(f_pos_i == ftell(f), "Something bad happened.\n");

	return read_bytes(f, bytes);
}

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
