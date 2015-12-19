/* `helper.h` -> Helper macros/functions
 */

#ifndef HELPER_H
#define HELPER_H

#define ASSERT(condition, message)\
	if (!(condition))             \
	{                             \
		fprintf(stderr, message); \
		exit(1);                  \
	}

#endif // HELPER_H
