#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3
#define ALIASES_H

/* for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 *struct passinfo - contains pseudo-arguements to pass into a function,
 *		allowing uniform prototype for function pointer struct
 *@arg: a string generated from getline containing arguements
 *@argv: an array of strings generated from arg
 *@path: a string path for the current command
 *@argc: the argument count
 *@line_count: the error count
 *@err_num: the error code for exit()s
 *@linecount_flag: if on count this line of input
 *@fname: the program filename
 *@env: linked list local copy of environ
 *@environ: custom modified copy of environ from LL env
 *@history: the history node
 *@alias: the alias node
 *@env_changed: on if environ was changed
 *@status: the return status of the last exec'd command
 *@cmd_buf: address of pointer to cmd_buf, on if chaining
 *@cmd_buf_type: CMD_type ||, &&, ;
 *@readfd: the fd from which to read line input
 *@histcount: the history line number count
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;


/* toem_shloop.c */
int hsh(info_t *, char **);
int find_builtin(info_t *);
void find_cmd(info_t *);
void fork_cmd(info_t *);

/* toem_parser.c */
int is_cmd(info_t *, char *);
char *dup_chars(char *, int, int);
char *find_path(info_t *, char *, char *);

/* loophsh.c */
int loophsh(char **);

/* toem_errors.c */
void _eputs(char *);
int _eputchar(char);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);

/* toem_string.c */
int _strlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);

/* toem_string1.c */
char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);

/* toem_exits.c */
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);

/* toem_tokenizer.c */
char **strtow(char *, char *);
char **strtow2(char *, char);

/* toem_realloc.c */
char *_memset(char *, char, unsigned int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);

/* toem_memory.c */
int bfree(void **);

/* toem_atoi.c */
int _myerratoi(info_t *);
int print_custom_error(char, char *);
int custom_print_d(int);
int _atoi(char *);

/* toem_errors1.c */
int _erratoi(char *);
void print_error(info_t *, char *);
int print_d(int, int);
char *convert_number(long int, int, int);
void remove_comments(char *);

/* toem_builtin.c */
int _my_custom_exit(info_t *);
int _my_custom_cd(info_t *);
int _my_custom_help(info_t *);

/* toem_builtin1.c */
int _my_custom_history(info_t *);
int custom_unset_alias(info_t *);

/*toem_getline.c */
ssize_t my_input_buf(info_t *);
int _custom_getline(info_t *, char **, size_t *);
void _custom_sigintHandler(int);

/* toem_getinfo.c */
void clear_custom_info(info_t *);
void custom_set_info(info_t *, char **);
void free_custom_info (info_t *, int);

/* toem_environ.c */
char *_my_custom_env(info_t *, const char *);
int _getenv_custom(info_t *);
int _custom_mysetenv(info_t *);
int _my_custom_unsetenv(info_t *);
int populate_env_custom_list(info_t *);

/* toem_getenv.c */
char **get_custom_environ(info_t *);
int _my_unsetenv(info_t *, char *);
int _setenv_custom(info_t *, char *, char *);

/* toem_history.c */
char *get_history_custom_file(info_t *info);
int my_write_history(info_t *info);
int my_read_history(info_t *info);
int my_build_history_list(info_t *info, char *buf, int linecount);
int my_renumber_history(info_t *info);

/* toem_lists.c */
list_t *abokhabaar3(list_t **, const char *, int);
list_t *ert(list_t **, const char *, int);
size_t ihatethis(const list_t *);
int banque(list_t **, unsigned int);
void cassh(list_t **);

/* toem_lists1.c */
size_t listkhamat(const list_t *);
char **listpeople(list_t *);
size_t abokhabar(const list_t *);
list_t *khabib(list_t *, char *, char);
ssize_t headache(list_t *, list_t *);

/* toem_vars.c */
int mymani(info_t *, char *, size_t *);
void mymanp(info_t *, char *, size_t *, size_t, size_t);
int mymanl(info_t *);
int mymank(info_t *);
int mymanj(char **, char *);

#endif
