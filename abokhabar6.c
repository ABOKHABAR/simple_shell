#include "myshell.h"


/**
 * _custom_str_to-int - converts a string to an integer
 * @custom_str: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 *       -1 on error
 *
 */

int _custom_str_to_int(char *custom_str)
{
	int custom_i = 0;
	unsigned long int custom_result = 0;

	if (*custom_str == '+')
	{
		custom_str++;
	}

	for (custom_i = 0; custom_str[custom_i] != '\0'; custom_i++)
	{
		if (custom_str[custom_i] >= '0' && custom_str[custom_i] <= '9')
		{
			custom_result *= 10;
			custom_result += (custom_str[custom_i] - '0');
			if (custom_result > CUSTOM_INT_MAX)
			{
				return (-1);
			}
		}
		else
		{
			return (-1);
		}
	}
	return (custom_result);
}


/**
 * custom_print_error - prints an error message
 * @custom_info: the parameter & return info struct
 * @custom_error_type: string containing specified error type
 * Return: 0 if no numbers in string, converted number otherwise
 *        -1 on error
 */

void custom_print_error(custom_info_t *custom_info, char *custom_error_type)
{
	_custom_err_puts(custom_info->custom_fname);
	_custom_err_puts(": ");
	custom_print_int(custom_info->custom_line_count, STDERR_FILENO);
	_custom_err_puts(": ");
	_custom_err_puts(custom_info->custom_argv[0]);
	_custom_err_puts(": ");
	_custom_err_puts(custom_error_type);
}

/**
 * custom_print_int - function prints a decimal (integer) number (base 10)
 * @custom_input: the input
 * @custom_fd: the filedescriptor to write to
 *
 * Return: number of characters printed
 */

int custom_print_int(int custom_input, int custom_fd)
{
	int (*custom_putchar_func)(char) = custom_putchar_func;
	int custom_i, custom_count = 0;
	unsigned int custom_abs, custom_current;

	if (custom_fd == STDERR_FILENO)
	{
		custom_putchar_func = custom_putchar_func;
	}

	if (custom_input < 0)
	{
		custom_abs = -custom_input;
		custom_putchar_func('-');
		custom_count++;
	}
	else
	{
		custom_abs = custom_input;
	}

	custom_current = custom_abs;
	for (custom_i = CUSTOM_INT_DIVISOR; custom_i > 1; custom_i /= 10)
	{
		if (custom_abs / custom_i)
		{
			custom_putchar_func('0' + custom_current / custom_i);
			custom_count++;
		}

		custom_current %= custom_i;
	}

	custom_putchar_func('0' + custom_current);
	custom_count++;
	return (custom_count);
}

/**
 * custom_convert_number - converter function, a clone of itoa
 * @custom_num: number
 * @custom_base: base
 * @custom_flags: argument flags
 *
 * Return: string
 */

char *custom_convert_number(int custom_num, int custom_base, int custom_flags)
{
	static char *custom_array;
	static char custom_buffer[CUSTOM_BUFFER_SIZE];
	char custom_sign = 0;
	char *custom_ptr;
	unsigned long custom_n = custom_num;

	if (!(custom_flags & CUSTOM_FLAG_UNSIGNED) && custom_num < 0)
	{
		custom_n = -custom_num;
		custom_sign = '-';
	}

	custom_array =
	(custom_flags & CUSTOM_FLAG_LOWERCASE)
	? "0123456789abcdef" : "0123456789ABCDEF";
	custom_ptr = &custom_buffer
		[CUSTOM_BUFFER_SIZE - 1];
	*custom_ptr = '\0';

	do

	{
		*--custom_ptr = custom_array[custom_n % custom_base];
		custom_n /= custom_base;
	}

	while (custom_n != 0);

	if (custom_sign)
	{
		*--custom_ptr = custom_sign;
	}

	return (custom_ptr);
}

/**
 * custom_remove_comments - function replaces first instance of '#' with '\0'
 * @custom_buf: address of the string to modify
 *
 * Return: Always 0;
 */

void custom_remove_comments(char *custom_buf)
{
	int custom_i;

	for (custom_i = 0; custom_buf[custom_i] != '\0'; custom_i++)
	{
		if (custom_buf[custom_i] == '#' &&
				(!custom_i || custom_buf[custom_i - 1] == ' '))
		{
			custom_buf[custom_i] = '\0';

			break;
		}
	}
}
