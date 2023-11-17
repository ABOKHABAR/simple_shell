#include "myshell.h"

/**
 * custom_buff - buffers chained commands
 * @custom_info: parameter struct
 * @custom_buf: address of buffer
 * @custom_len: address of len var
 *
 * Return: bytes read
 */

ssize_t custom_buff(info_t *custom_info, char **custom_buf, size_t *custom_len)
{
	ssize_t custom_r = 0;
	size_t custom_len_p = 0;

	if (!*custom_len)
	{
		free(*custom_buf);
		*custom_buff = NULL;
		signal(SIGINT, _custom_sigint_handler);
#if USE_CUSTOM_GETLINE
		custom_r = _custom_getline(custom_buf, &custom_len_p, stdin);
#else
		custom_r = _custom_get_line(custom_info, custom_buf, &custom_len_p);
#endif
		if (custom_r > 0)
		{
			if ((*custom_buf)[custom_r - 1] == '\n')
			{
				(*custom_buf)[custom_r - 1] = '\0';
				custom_r--;
			}
			custom_info->linecount_flag = 1;
			_custom_remove_comments(*custom_buf);
			_custom_build_history_list
				(custom_info, *custom_buf, custom_info->histcount++);
			custom_len = custom_r;
			custom_info->cmd_buf = custom_buf;
		}
	}
	return (custom_r);
}


/**
 * _custom_get_input - gets a line minus the newline
 * @custom_info: parameter struct
 *
 * Return: bytes read
 */

ssize_t _custom_get_input(info_t *custom_info)
{
	static char *custom_buf;
	static size_t custom_i, custom_j, custom_len;
	ssize_t custom_r = 0;
	char **custom_buf_p = &(custom_info->arg), *custom_p;

	_custom_put_char(BUF_FLUSH);
	custom_r = _custom_input_buffer(custom_info, &custom_buf, &custom_len);
	if (custom_r == -1)
	{
		return (-1);
	}
	if (custom_len)
	{
		custom_j = custom_i;
		custom_p = custom_buf + custom_i;

		_custom_check_chain
		(custom_info, custom_buf, &custom_j, custom_i, custom_len);
		while (custom_j < custom_len)
		{
			if (_custom_is_chain(custom_info, custom_buf, &custom_j))
			{
				break;
			}
			custom_j++;
		}
		custom_i = custom_j + 1;
		if (custom_i >= custom_len)
		{
			custom_i = custom_len = 0;
			custom_info->cmd_buf_type = CMD_NORM;
		}
		*custom_buf_p = custom_p;
		return (_custom_string_length(custom_p));
	}
	*custom_buf_p = custom_buf;
	return (custom_r);
}

/**
 * custom_buffer - reads a buffer
 * @custom_info: parameter struct
 * @custom_buf: buffer
 * @custom_i: size
 *
 * Return: r
 */

ssize_t custom_buffer(info_t *custom_info, char *custom_buf, size_t *custom_i)
{
	ssize_t custom_r = 0;

	if (*custom_i)
	{
		return (0);
	}
	custom_r = read(custom_info->readfd, custom_buf, READ_CUSTOM_BUF_SIZE);
	if (custom_r >= 0)
	{
		*custom_i = custom_r;
	}
	return (custom_r);
}


/**
 * custom_line - gets the next line of input from STDIN
 * @custom_info: parameter struct
 * @custom_ptr: address of pointer to buffer, preallocated or NULL
 * @custom_length: size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */

ssize_t _r_buffer(info_t *custom_info, char *custom_buf, size_t *custom_len)
{
	char **custom_ptr;
	size_t *custom_length;
	char *custom_buf;
	size_t custom_len;
	ssize_t custom_r;

	if (*custom_len == 0)
	{
		*custom_len = 0;
		custom_r = _custom_read_buffer(custom_info, custom_buf, custom_len);

		if (custom_r == -1 || (custom_r == 0 && *custom_len == 0))
		{
			return (-1);
		}
	}
	return (custom_r);

	size_t custom_i;
	char *custom_c = _custom_find_char(custom_buf + custom_i, '\n');
	size_t custom_k = custom_c ? 1 +
		(unsigned int)(custom_c - custom_buf) : custom_len;
	size_t new_length = *custom_length + custom_k - custom_i;
	char *custom_p = *custom_ptr;
	char *custom_new_p = _custom_realloc
		(custom_p, *custom_length, new_length + 1);

	if (!custom_new_p)
	{
		return (custom_p ? (free(custom_p), -1) : -1);
	}

	_custom_concatenate_string
		(custom_new_p, custom_buf + custom_i, custom_k - custom_i);
	*custom_length = new_length;
	*custom_ptr = custom_new_p;

	return (custom_c || custom_len == 0 ? 0 : 1);
}

ssize_t custom_line(info_t *custom_info, char **custom_ptr, size_t *c_length)
{
	static char custom_buf[READ_CUSTOM_BUF_SIZE];
	static size_t custom_i, custom_len;
	ssize_t custom_r;

	int sig_num __attribute__((unused))
	char *custom_p = *custom_ptr;

	if (custom_p && custom_length)
	{
		*custom_length = 0;
	}

	while (1)
	{
		custom_r = _custom_read_into_buffer(custom_info, custom_buf, &custom_len);
		if (custom_r == -1)
		{
			return (-1);
		}

		int result = _custom_process_buffer
			(&custom_p, custom_length, custom_buf, custom_i, custom_len);

		if (result == -1)
		{
			return (-1);
		}

		if (result == 0)
		{
			break;
		}
	}
	*custom_ptr = custom_p;
	return (*custom_length);

	_custom_puts("\n");
	_custom_puts("$ ");
	_custom_put_char(BUF_FLUSH);
}
