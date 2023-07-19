#include "shell.h"

/**
 * init_data - Initializes the program data
 * @data: Program data
 * Return: void
 */
void init_data(shell_info *data)
{
	char **env;
	char *var;
	int i;

	env = malloc(64 * sizeof(char *));
	if (!env)
	{
		perror("Allocation error");
		exit(EXIT_FAILURE);
	}
	for (i = 0; environ[i]; i++)
	{
		var = _strdup(environ[i]);
		env[i] = var;
	}
	env[i] = NULL;
	environ = env;

	data->cmd = NULL;
	data->cmdline = NULL;
	data->execution_count = 0;
	data->args = NULL;
}

/**
 * is_builtin - Checks if the current command is builtin
 * @data: Program data
 * Return: The exit code of the builtin command
 * execution process else -1 if not builtin
 */
int is_builtin(shell_info *data)
{
	int i = 0;
	builtin_action actions[] = {
		{"exit", builtin_exit},
		{"env", print_environment},
		{"setenv", builtin_setenv},
		{"unsetenv", builtin_unsetenv},
		{NULL, NULL}};

	while (actions[i].cmd)
	{
		if (_strcmp(data->args[0], actions[i].cmd) == 0)
			return (actions[i].action(data));
		i++;
	}

	return (-1);
}

/**
 * check_exec - Checks if a file exits and it's an executable
 * @args: Path to the file
 * Return: 1 if all conditions are satisfied.
 */
int check_exec(char *args)
{
	struct stat fileStatus;

	/* If path exists */
	if (stat(args, &fileStatus) == 0)
	{
		/* If path is a directory or is not an executable */
		if (access(args, X_OK) || S_ISDIR(fileStatus.st_mode))
		{
			errno = 126;
			return (126);
		}
		return (1);
	}
	errno = 127;
	return (127);
}
