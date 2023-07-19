#include "shell.h"

/**
 * build_command_list - Builds the command list for a
 * single command line
 * @data: Program data
 * Return: void
 */
void build_command_list(shell_info *data)
{
	char **commands;
	char *command;
	int i = 0;

	commands = malloc(MAX_TOKENS * sizeof(char *));
	if (!commands)
	{
		perror("Allocation error");
		exit(EXIT_FAILURE);
	}

	while ((command = _strdup(_strtok(i ? NULL : data->cmdline, ";"))))
		commands[i++] = command;
	commands[i] = NULL;
	data->cmdlist = commands;
}

/**
 * check_comment - Checks if a comment exist in a command
 * @data: Program data
 * Return: 1 if comment else 0
 */
int check_comment(shell_info *data)
{
	int i;

	for (i = 0; data->cmd[i]; i++)
	{
		if (data->cmd[i] == '#')
		{
			if (i == 0)
			{
				data->cmd = "";
				return (1);
			}

			data->cmd = _strtok(data->cmd, "#");
			return (1);
		}
	}
	return (0);
}
