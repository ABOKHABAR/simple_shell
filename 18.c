#include "myshell.h"

/**
 ** fnx1 - fills memory with a constant byte
 *@s: the pointer to the memory area
 *@b: the byte to fill *s with
 *@n: the amount of bytes to be filled
 *Return: (s) a pointer to the memory area s
 */

char *fnx1(char *s, char b, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		s[i] = b;
	return (s);
}

/**
 * fnx2 - frees a string of strings
 * @pp: string of strings
 */

void fnx2(char **pp)
{
	char **a = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(a);
}

/**
 * fnx3 - reallocates a block of memory
 * @p: pointer to previous malloc'ated block
 * @old_size: byte size of previous block
 * @new_size: byte size of new block
 *
 * Return: pointer to da ol'block nameen.
 */

void *fnx3(void *p, unsigned int old_size, unsigned int new_size)
{
	char *np;

	if (!p)
		return (malloc(new_size));
	if (!new_size)
		return (free(p), NULL);
	if (new_size == old_size)
		return (p);

	np = malloc(new_size);
	if (!np)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		np[old_size] = ((char *)p)[old_size];
	free(p);
	return (np);
}
