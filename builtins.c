#include <unistd.h>
#include "shell.h"

/**
 * print_environment - Handles the `env` built-in command
 * @data: Program data
 * Return: The status of the execution
 */
int print_environment(shell_info *data)
{
	int i = 0;

	(void)data;

	while (environ[i] != NULL)
	{
		write(STDOUT_FILENO, environ[i], _strlen(environ[i]));
		write(STDOUT_FILENO, "\n", 1);
		i++;
	}
	return (EXIT_SUCCESS);
}

/**
 * builtin_exit - Handles the builtin exit command
 * @data: Program data
 * Return: Nothing
 */
int builtin_exit(shell_info *data)
{
	int status = EXIT_SUCCESS; /*this is the default exit status */

	if (data->args[1] != NULL)
		status = _atoi(data->args[1]);

	free_array_of_pointers(data->args);
	free(data->cmdline);
	exit(status);
}
