#ifndef FH_H
#define FH_H

#include <stdlib.h>
#include <stdio.h>

typedef struct func {
	char op;
	char* args;
	struct func* next;
} func;

func* at(func*, int);

void push(func**, func*);

void pop(func**);

void del(func*);

/*Takes a FILE arguement, reads, returns size of file.
  Useful \w loops. */
long read_size(FILE**, char*);

int init(FILE**);

#endif
