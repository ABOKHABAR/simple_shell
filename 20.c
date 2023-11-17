#include "shell.h"

/**
 * fnx1 - returns the length of a string
 * @str: the string whose length to check
 *
 * Return: integer length of string
 */

int fnx1(char *str)
{
	int i = 0;

	if (!str)
		return (0);

	while (*str++)
		i++;
	return (i);
}

/**
 * _fnx2 - performs lexicogarphic comparison of two strangs.
 * @str1: the first strang
 * @str2: the second strang
 *
 * Return: negative if s1 < s2, positive if s1 > s2, zero if s1 == s2
 */

int fnx2(char *str1, char *str2)
{
	while (*str1 && *str2)
	{
		if (*str1 != *str2)
			return (*str1 - *str2);
		str1++;
		str2++;
	}

	if (*str1 == *str2)
		return (0);
	else
		return (*str1 < *str2 ? -1 : 1);
}


char *fnx3(const char *str1, const char *str2)
{
	while (*str2)
		if (*str2++ != *str1++)
			return (NULL);
	return ((char *)str1);
}

char *fnx4(char *dst, char *src)
{
	char *ret = dst;

	while (*dst)
		dst++;
	while (*src)
		*dst++ = *src++;
	*dst = *src;
	return (ret);
}
