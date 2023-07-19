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
	free_array_of_pointers(environ);
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
	char *var = data->args[1];
	char *val = data->args[2];
	char *env;
	int i, len = _strlen(var);

	if (!var || !val)
	{
		perror("Invalid argument for setenv\n");
		return (-1);
	}

	env = malloc(len + _strlen(val) + 2);
	if (!env)
	{
		perror("Allocation error\n");
		return (-1);
	}

	_strcpy(env, var);
	_strcat(env, "=");
	_strcat(env, val);

	for (i = 0; environ[i]; i++)
	{
		if (_strncmp(environ[i], var, len) == 0 && environ[i][len] == '=')
		{
			free(environ[i]);
			environ[i] = env;
			free(env);
			return (0);
		}
	}
	free(environ[i]);
	environ[i] = env;
	environ[i + 1] = NULL;
	return (0);
}
/**
 *  builtin_unsetenv - deletes an existing env variable
 *  @data: Program data
 *  Return: 0 if successful
 */
int builtin_unsetenv(shell_info *data)
{
	char *var = data->args[1];
	char *env = _getenv(var);
	int len = _strlen(var);
	int i, found = 0;

	if (!env)
		return (-1);
	for (i = 0; environ[i]; i++)
	{
		if (!found)
		{
			if (_strncmp(environ[i], var, len) == 0 && environ[i][len] == '=')
			{
				free(environ[i]);
				found = 1;
			}
			continue;
		}
		environ[i - 1] = environ[i];
	}
	environ[i - 1] = NULL;
	return (0);
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
		/*_setenv("PWD", pwd);*/
	}
	return (status);
}
