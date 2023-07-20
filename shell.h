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
 * struct od - Operation Data
 * @operands: The operands in the operation
 * @operators: The operators in the operation
 */
typedef struct od
{
	char **operands;
	int operators[MAX_TOKENS];
} ops_data;

/**
 * struct pd - Program Data
 * @name: Path of the shell when ran
 * @execution_count: Tracks the number of commands executed
 * @cmd: The current running command
 * @args: Current command arguments
 * @cmdline: The command read from stdin
 * @cmdlist: The commands available in a command line
 * @logic_data: Data related to the logical operation of a single command.
 */
typedef struct pd
{
	char *name;
	int execution_count;
	char *cmd;
	char **args;
	char *cmdline;
	char **cmdlist;
	ops_data *logic_data;

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
int _strcmp(char *s1, char *s2);
char *_strtok(char *s, char *delim);
char *_strdup_range(char *src, int from, int to);

/* other relevant functions */
void _memcpy(void *dest, const void *src, size_t n);
void free_array_of_pointers(char **arr);
void free_program_data(shell_info *data);
void free_all_data(shell_info *data);

/* command line interpreter functions */
ssize_t read_line(shell_info *data);
void tokenize_input(shell_info *data);
char *_getenv(const char *name);
char *handle_path(char *args);
int check_exec(char *args);
int exec_command(shell_info *data);
void shell_loop(char *prompt, shell_info *data);
int is_builtin(shell_info *data);
void init_data(shell_info *data);
void build_command_list(shell_info *data);
int check_comment(shell_info *data);
ops_data *expand_logical_ops(char *cmd, ops_data *data);

/* Builtin command handlers */
int print_environment(shell_info *data);
int builtin_exit(shell_info *data);
int builtin_cd(shell_info *data);

/* Output */
void print_error(shell_info *data);

/* Converters */
void number_to_string(char *buf, int num);
void reverse_string(char *str);
int _atoi(char *str);
#endif
