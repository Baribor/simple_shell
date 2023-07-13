#include "shell.h"

/**
 * shell_loop - Main shell loop
 * @prompt: The prompt to show, Enter string for
 * non-interractive mode
 * @data: Data of the shell
 */
void shell_loop(char *prompt, shell_info *data)
{
	char *line;
	char **args;
	int builtin;

	while (++(data->execution_count))
	{
		write(1, prompt, _strlen(prompt));
		line = read_line();

		if (line[0] == '\0')
		{
			free(line);
			continue;
		}

		args = tokenize_input(line);
		data->cmd = args[0];
		builtin = is_builtin(data);

		if (builtin == -1)
			exec_command(args);

		free(args);
		free(line);
	}
}
