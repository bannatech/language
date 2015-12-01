#include <stdlib.h>
#include <stdio.h>

#include "fh.h"

func* at(func* root, int x)
{
	x--;

	if (root->next == NULL)
	{
		return root;
	}
	else
	{
		return at(root->next, x);
	}
}

void push(func** root, func* new_node)
{
	new_node->next = *root;
	*root = new_node;
}

void pop(func** root)
{
	if ((*root)->next != NULL)
	{
		func *old_node = (*root)->next;
		free(*root);
		*root = old_node;
	}
}

void del(func* root)
{
	if (root->next != NULL)
	{
		del(root->next);
	}

	free(root);
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

int init(FILE** f)
{
	/* initialize datastructures for instructionstuffs,
	   begin to read file byte-by-byte */
	return 0;
}
