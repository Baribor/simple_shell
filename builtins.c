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

	free_all_data(data);
	exit(status);
}
/**
 * builtin_setenv - Initialize a new environment variable
 * @data: program data
 * Return: 0 if successful otherwise, -1
 */
int builtin_setenv(shell_info *data)
{
	int temp = _setenv(data->args[1], data->args[2]);

	return (temp);
}
/**
 *  builtin_unsetenv - deletes an existing env variable
 *  @data: Program data
 *  Return: 0 if successful
 */
int builtin_unsetenv(shell_info *data)
{
	int temp = _unsetenv(data->args[1]);

	return (temp);
}

/**
 * builtin_cd - Handles the cd command
 * @data: Program data
 * Return: The status of the execution
 */
int builtin_cd(shell_info *data)
{
	char *dir = data->args[1];
	char pwd[MAX_DIR_LENGTH] = {'\0'};
	int status;

	/* Check if no argument or - was passed */
	if (dir == NULL || _strcmp(dir, "-") == 0)
		dir = _getenv("HOME");

	status = chdir(dir);
	if (status == EXIT_SUCCESS)
	{
		getcwd(pwd, MAX_DIR_LENGTH);
		_setenv("PWD", pwd);
	}
	return (status);
}
