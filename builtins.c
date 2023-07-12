#include <unistd.h>
#include "shell.h"

void print_environment()
{
	extern char **environ;
	int i = 0;

	while (environ[i] != NULL)
	{
		write(STDOUT_FILENO, environ[i], _strlen(environ[i]));
		write(STDOUT_FILENO, "\n", 1);
		i++;
	}
}
