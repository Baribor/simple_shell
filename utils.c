#include "shell.h"

/**
 * init_data - Initializes the program data
 * @data: Program data
 * Return: void
 */
void init_data(shell_info *data)
{
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
		{BUILTIN_EXIT, builtin_exit},
		{BUILTIN_CD, builtin_cd},
		{BUILTIN_ENV, print_environment},
		{NULL, NULL}};

	while (actions[i].cmd)
	{
		if (_strcmp(data->args[0], actions[i].cmd) == 0)
			return (actions[i].action(data));
		i++;
	}

	return (NOT_BUILTIN);
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
			return (COMMAND_ERROR);
		}
		return (1);
	}
	errno = 127;
	return (COMMAND_ERROR);
}
