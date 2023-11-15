#include "myshell.h"

/**
 **_custom_copy_str - copies a string
 *@custom_dest: the destination string to be copied to
 *@custom_src: the source string
 *@custom_n: the amount of characters to be copied
 *Return: the concatenated string
 */

char *_custom_copy_str(char *custom_dest, char *custom_src, int custom_n)
{
	int custom_i, custom_j;
	char *custom_s = custom_dest;

	custom_i = 0;
	while (custom_src[custom_i] != '\0' && custom_i < custom_n - 1)
	{
		custom_dest[custom_i] = custom_src[custom_i];
		custom_i++;
	}

	if (custom_i < custom_n)
	{
		custom_j = custom_i;
		while (custom_j < custom_n)
		{
			custom_dest[custom_j] = '\0';
			custom_j++;
		}
	}
	return (custom_s);
}

/**
 ** custom_concatenate_str - concatenates two strings
 *@custom_dest: the first string
 *@custom_src: the second string
 *@custom_n: the amount of bytes to be maximally used
 *Return: the concatenated string
 */

char *custom_concatenate_str(char *custom_dest, char *custom_src, int custom_n)
{
	int custom_i, custom_j;
	char *custom_s = custom_dest;

	custom_i = 0;
	custom_j = 0;
	while (custom_dest[custom_i] != '\0')
	{
		custom_i++;
	}

	while (custom_src[custom_j] != '\0' && custom_j < custom_n)
	{
		custom_dest[custom_i] = custom_src[custom_j];
		custom_i++;
		custom_j++;
	}

	if (custom_j < custom_n)
	{
		custom_dest[custom_i] = '\0';
	}
	return (custom_s);
}


/**
 **_custom_find_char - locates a character in a string
 *@custom_str: the string to be parsed
 *@custom_c: the character to look for
 *Return: (s) a pointer to the memory area s
 */

char *_custom_find_char(char *custom_str, char custom_c)
{
	do

	{
		if (*custom_str == custom_c)
		{
			return (custom_str);
		}

	}

	while (*custom_str++ != '\0');
	return (NULL);
}
