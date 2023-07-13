#include "shell.h"

/**
 * init_data - Initializes the program data
 * @data: Program data
 * Return: void
 */
void init_data(shell_info *data)
{
	data->cmd = NULL;
	data->execution_count = 0;
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
		{NULL, NULL}};

	while (actions[i].cmd)
	{
		if (strcmp(data->cmd, actions[i].cmd) == 0)
			return (actions[i].action(data));
		i++;
	}

	return (-1);
}

/**
 * check_exec - Checks if a file exits and it's an executable
 * @args: Path to the file
 * Return: 1 if all conditions are satisfied, else 0
 */
int check_exec(char *args)
{
	return (access(args, X_OK) == 0 && access(args, F_OK) == 0);
}
