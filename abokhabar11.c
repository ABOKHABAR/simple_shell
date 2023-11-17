#include "myshell.h"

/**
 * _custom_get_custom_history_file - gets the history file
 * @custom_info: parameter struct
 *
 * Return: allocated string containg history file
 */

char *_custom_get_custom_history_file(info_t *custom_info)
{
	char *custom_buf, *custom_dir;

	custom_dir = _custom_getenv(custom_info, "HOME=");
	if (!custom_dir)
	{
		return (NULL);
	}
	custom_buf = _custom_malloc(sizeof(char) *
			(_custom_strlen(custom_dir) + _custom_strlen(CUSTOM_HIST_FILE) + 2));
	if (!custom_buf)
	{
		return (NULL);
	}
	custom_buf[0] = 0;
	_custom_strcpy(custom_buf, custom_dir);
	_custom_strcat(custom_buf, "/");
	_custom_strcat(custom_buf, CUSTOM_HIST_FILE);
	return (custom_buf);
}

/**
 * _custom_write_custom_history - creates, or appends to an existing file
 * @custom_info: the parameter struct
 *
 * Return: 1 on success, else -1
 */

int _custom_write_custom_history(info_t *custom_info)
{
	ssize_t custom_fd;
	char *custom_filename = _custom_get_custom_history_file(custom_info);
	list_t *custom_node = NULL;

	if (!custom_filename)
	{
		return (-1);
	}

	custom_fd = _custom_open(custom_filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	_custom_free(custom_filename);
	if (custom_fd == -1)
	{
		return (-1);
	}
	for (custom_node = custom_info->custom_history; custom_node;
			custom_node = custom_node->next)
	{
		_custom_putsfd(custom_node->str, custom_fd);
		_custom_putfd('\n', custom_fd);
	}
	_custom_putfd(CUSTOM_BUF_FLUSH, custom_fd);
	_custom_close(custom_fd);
	return (1);
}


/**
 * _custom_read_custom_history - reads history from file
 * @custom_info: the parameter struct
 *
 * Return: histcount on success, 0 otherwise
 */
int _custom_read_custom_history(info_t *custom_info)
{
	char *custom_filename = _custom_get_custom_history_file(custom_info);

	if (!custom_filename)
	{
		return (0);
	}
	int custom_fd = _custom_open(custom_filename, O_RDONLY);

	_custom_free(custom_filename);
	if (custom_fd == -1)
	{
		return (0);
	}
	ssize_t custom_fsize;
	struct stat custom_st;

	if (!_custom_fstat(custom_fd, &custom_st))
		custom_fsize = custom_st.st_size;
	if (custom_fsize < 2)
	{
		_custom_close(custom_fd);
		return (0);
	}
	char *custom_buf = _custom_malloc(sizeof(char) * (custom_fsize + 1));

	if (!custom_buf)
	{
		_custom_close(custom_fd);
		return (0);
	}
	ssize_t custom_rdlen = _custom_read(custom_fd, custom_buf, custom_fsize);

	custom_buf[custom_fsize] = 0;
	_custom_close(custom_fd);
	if (custom_rdlen <= 0)
	{
		_custom_free(custom_buf);
		return (0);
	}
}
int _custom_process_custom_history
(info_t *custom_info, char *custom_buf, ssize_t custom_fsize);
{
	int custom_i, custom_last = 0, custom_linecount = 0;

	for (custom_i = 0; custom_i < custom_fsize; custom_i++)
	{
		if (custom_buf[custom_i] == '\n')
		{
		custom_buf[custom_i] = 0; _custom_build_custom_history_list
				(custom_info, custom_buf + custom_last, custom_linecount++);
			custom_last = custom_i + 1;
		}
	}
	if (custom_last != custom_i)
	{
		_custom_build_custom_history_list
			(custom_info, custom_buf + custom_last, custom_linecount++);
	}
	_custom_free(custom_buf);
	custom_info->custom_histcount = custom_linecount;
	while (custom_info->custom_histcount-- >= CUSTOM_HIST_MAX)
	{
		_custom_delete_custom_node_at_index(&(custom_info->custom_history), 0);
	}
	_custom_renumber_custom_history(custom_info);
		return (custom_info->custom_histcount);
}
/**
 * custom_history - adds entry to a history linked list
 * @custom_info: Structure containing potential arguments. Used to maintain
 * @custom_buf: buffer
 * @custom_linecount: the history linecount, histcount
 *
 * Return: Always 0
 */

int custom_history(info_t *custom_info, char *custom_buf, int custom_linecount)
{
	list_t *custom_node = NULL;

	if (custom_info->custom_history)
	{
		custom_node = custom_info->custom_history;
	}
	_custom_add_custom_node_end(&custom_node, custom_buf, custom_linecount);
	if (!custom_info->custom_history)
	{
		custom_info->custom_history = custom_node;
	}
	return (0);
}
