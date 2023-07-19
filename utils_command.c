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
