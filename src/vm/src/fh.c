#include <stdio.h>
#include <stdlib.h>

#include "fh.h"

void read_until_null(FILE** f, long* f_pos, byte_t** buffer)
{
	long f_pos_i = *f_pos;
	while (fgetc(*f) != NULL) (*f_pos)++;

	long bytes = *f_pos - f_pos_i;
	fseek(*f, -bytes, SEEK_CUR);
	*f_pos = f_pos_i;

	read_bytes(f, f_pos, bytes, buffer);
}

void read_bytes(FILE** f, long* f_pos, int bytes, byte_t** buffer)
{
	*buffer = (byte_t*)malloc(bytes*sizeof(byte_t));
	if (*buffer == NULL)
		return;
	fread(*buffer, bytes, 1, *f);
	*f_pos = *f_pos + bytes;
}

byte_t read_byte(FILE** f, long* f_pos)
{
	byte_t byte = fgetc(*f);
	(*f_pos)++;
	return byte;
}

long read_size(FILE** f, char* fname)
{
	*f = fopen(fname, "rb");
	fseek(*f, 0, SEEK_END);

	long fsize = 0;
	fsize = ftell(*f);
	rewind(*f);

	return fsize;
}
