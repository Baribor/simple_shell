#ifndef SHELL_H
#define SHELL_H

#define MAX_TOKENS 64
#define DELIM " \t\r\n\a"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <dirent.h>

/*string functions*/
char *_strcat(char *dest, const char *src);
char *_strcpy(char *dest, const char *src);
size_t _strlen(const char *str);
int _strncmp(const char *s1, const char *s2, size_t n);
size_t _strcspn(char *str, char *charset);

/* command line interpreter functions */
char *read_line();
char **tokenize_input(char *line);
char *_getenv(const char *name);
char *handle_path(char *args);
int check_exec(char *args);
void exec_command(char **args);
void print_error();
void print_environment();
int is_eof();
void handle_eof();
void shell_loop();

#endif
