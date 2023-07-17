#ifndef _SHELL_MACROS
#define _SHELL_MACROS

#define MAX_TOKENS 64
#define MAX_TOKEN_SIZE 32
#define MAX_DIR_LENGTH 4096
#define BUF_SIZE 1024
#define DELIM " \t\r\n\a"

#define PROMPT "($) "
#define NOT_BUILTIN -99
#define COMMAND_ERROR -1

/* Builtins */
#define BUILTIN_CD "cd"
#define BUILTIN_ENV "env"
#define BUILTIN_EXIT "exit"
#endif
