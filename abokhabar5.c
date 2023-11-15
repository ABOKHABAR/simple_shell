#include "myshell.h"


/**
 *_custom_print_error - prints an input string
 * @custom_str: the string to be printed
 *
 * Return: Nothing
 */

void _custom_print_error(char *custom_str)
{
	int custom_i = 0;

	if (!custom_str)
		return;
	while (custom_str[custom_i] != '\0')

	{
		_custom_print_error(*custom_str[custom_i]);
		custom_i++;
	}
}


/**
 * _custom_put_error_char - writes the character c to stderr
 * @custom_c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */

int _custom_put_error_char(char custom_c)
{
	static int custom_i;
	static char custom_buf[CUSTOM_WRITE_BUF_SIZE];

	if (custom_c == CUSTOM_BUF_FLUSH || custom_i >= CUSTOM_WRITE_BUF_SIZE)

	{
		write(2, custom_buf, custom_i);
		custom_i = 0;
	}

	if (custom_c != CUSTOM_BUF_FLUSH)

	{
		custom_buf[custom_i++] = custom_c;
	}

	return (1);
}


/**
 * _custom_put_char_fd - writes the character c to given fd
 * @custom_c: The character to print
 * @custom_fd: The filedescriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */

int _custom_put_char_fd(char custom_c, int custom_fd)
{
	static int custom_i;
	static char custom_buf[CUSTOM_WRITE_BUF_SIZE];

	if (custom_c == CUSTOM_BUF_FLUSH || custom_i >= CUSTOM_WRITE_BUF_SIZE)
	{
		write(custom_fd, custom_buf, custom_i);
		custom_i = 0;
	}
	if (custom_c != CUSTOM_BUF_FLUSH)
	{
		custom_buf[custom_i++] = custom_c;
	}
	return (1);
}


/**
 *_custom_puts_fd - prints an input string
 * @custom_str: the string to be printed
 * @custom_fd: the filedescriptor to write to
 *
 * Return: the number of chars put
 */

int _custom_puts_fd(char *custom_str, int custom_fd)
{
	int custom_i = 0;

	if (!custom_str)
	{
		return (0);
	}
	while (*custom_str)
	{
		custom_i += _custom_put_char_fd(*custom_str++, custom_fd);
	}
	return (custom_i);
}
