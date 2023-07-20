#include "shell.h"

/**
 * expand_logical_ops - Expands the logical operands in a command
 * @cmd: A command
 * @data: The operation data
 * Return: The ops data
 */
ops_data *expand_logical_ops(char *cmd, ops_data *data)
{
	char *cmd_copy = _strdup(cmd);
	int len = _strlen(cmd_copy);
	int start = 0, idx = 0, oIdx = 0;

	data->operands = malloc(MAX_TOKENS * sizeof(char *));
	if (!data->operands)
	{
		perror("Allocation error");
		exit(EXIT_FAILURE);
	}

	while (*cmd_copy)
	{
		if (_strncmp(cmd_copy, "||", 2) == 0 || _strncmp(cmd_copy, "&&", 2) == 0)
		{
			data->operands[oIdx] = _strdup_range(cmd, start, idx);
			data->operators[oIdx++] = cmd_copy[0] == '|' ? LOGICAL_OR : LOGICAL_AND;
			start = idx + 2;
			cmd_copy += 2;
			idx += 2;
			continue;
		}
		cmd_copy++;
		idx++;
	}
	data->operands[oIdx] = _strdup_range(cmd, start, idx);
	free(cmd_copy - len);
	return (data);
}
