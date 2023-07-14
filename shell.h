#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <dirent.h>
#include <errno.h>

#include "shell_macros.h"

extern char **environ;
extern int errno;

/**
 * struct pd - Program Data
 * @name: Path of the shell when ran
 * @execution_count: Tracks the number of commands executed
 * @cmd: The current running command
 */
typedef struct pd
{
	char *name;
	int execution_count;
	char *cmd;
} shell_info;

/**
 * struct bf - Builtin-function
 * @cmd: The builtin command
 * @action: The function to handle the command
 */
typedef struct bf
{
	char *cmd;
	int (*action)(shell_info *data);
} builtin_action;

/*string functions*/
char *_strcat(char *dest, const char *src);
char *_strcpy(char *dest, const char *src);
size_t _strlen(const char *str);
int _strncmp(const char *s1, const char *s2, size_t n);
size_t _strcspn(char *str, char *charset);
char *_strdup(const char *str);

/* other functions */
void _memcpy(void *dest, const void *src, size_t n);

/* command line interpreter functions */
char *read_line();
char **tokenize_input(char *line);
char *_getenv(const char *name);
char *handle_path(char *args);
int check_exec(char *args);
int exec_command(char **args);
int is_eof(int fd);
void handle_eof(void);
void shell_loop(char *prompt, shell_info *data);
int is_builtin(shell_info *data);
void init_data(shell_info *data);

/* Builtin command handlers */
int print_environment(shell_info *data);
int builtin_exit(shell_info *data);

/* Output */
void print_error(int code, shell_info *data);

/* Converters */
void number_to_string(char *buf, int num);
void reverse_string(char *str);

#endif
