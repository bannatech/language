#include <stdio.h>

#include "fh.h"

int main(int argc, char** argv)
{
	if (argc < 2) return -1;

	/* START TESTING STUFF */
	FILE* f;
	long i = 0;
	long fsize = read_size(&f, argv[1]);

	while (i<fsize)
	{
		int test = fgetc(f);
		i++;
		printf("%x\n", (unsigned)test);
	}

	fclose(f);
	/* END TESTING STUFF */

	return 0;
}
