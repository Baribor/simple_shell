#include "shell.h"

void shell_loop(void)
{
	char *line;
	char **args;

	while (1)
	{
		write(1, "$ ", 2);
		line = read_line();

		if (line[0] == '\0')
		{
			free(line);
			continue;
		}

		args = tokenize_input(line);
		if (strcmp(args[0], "exit") == 0)
		{
			free(args);
			free(line);
			break;
		}
		else if (strcmp(args[0], "env") == 0)
			print_environment();
		else
			exec_command(args);
		
		free(args);
		free(line);
	}
}
