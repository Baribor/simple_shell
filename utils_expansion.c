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

	data->operands = calloc(MAX_TOKENS, sizeof(char *));
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

/**
 * expand_variables - Expands the variables in a command line
 * @line: The command line
 * @data: The Program data
 * Return: The expanded line
 */
char *expand_variables(char *line, shell_info *data)
{
	char num[10] = {'\0'};
	char *env;
	char var_buf[MAX_TOKENS] = {'\0'};
	int cIdx = 0, nIdx = 0, i, j, env_found;

	if (!line)
		return (NULL);
	while (*line)
	{
		if (*line == '$' && !(*(line + 1) == ' ' || *(line + 1) == '\0'))
		{
			if (((*(line + 1) == '$') || *(line + 1) == '?'))
			{
				number_to_string(num, *(line + 1) == '$' ? getpid() : errno);
				for (i = 0; num[i]; i++, cIdx++)
					data->cmdlinebuf[cIdx] = num[i];
				line += 2, nIdx += 2;
				continue;
			}
			env_found = 0;
			for (i = 1; *(line + i) && *(line + i) != ' ' && *(line + i) != '$'; i++)
			{
				var_buf[i - 1] = *(line + i), var_buf[i] = '\0', env = _getenv(var_buf);
				if (env)
				{
					env_found = 1;
					for (j = 0; env[j]; j++, cIdx++)
						data->cmdlinebuf[cIdx] = env[j];
					break;
				}
			}
			line += env_found ? i + 1 : i, nIdx += env_found ? i + 1 : i;
			continue;
		}
		data->cmdlinebuf[cIdx++] = *line;
		nIdx++, line++;
	}
	data->cmdlinebuf[cIdx] = '\0';
	free(line - nIdx);
	return (_strdup(data->cmdlinebuf));
}

/**
 * expand_alias - Expands and alias in a command line
 * @line: Command line
 * @data: Program data
 * Return: The expanded line
 */
char *expand_alias(char *line, shell_info *data)
{
	char var_buf[MAX_DIR_LENGTH] = {'\0'};
	/* int cIdx = 0, nIdx = 0, i = 0, j; */
	int i = 0;
	alias_list *alias;

	if (!line)
		return (NULL);

	while (*line)
	{
		if (*line == ' ')
		{
			var_buf[i] = '\0';
			alias = get_alias(data, var_buf);

			if (alias)
			{
				_strcpy(data->cmdlinebuf, alias->value);
			}
			else
			{
				var_buf[i] = ' ', var_buf[i + 1] = '\0';
				_strcpy(data->cmdlinebuf, var_buf);
			}
		}
		else
		{
			var_buf[i++] = *line;
		}
	}

	return (data->cmdlinebuf);
}
