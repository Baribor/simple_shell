#include "shell.h"

/**
 * shell_loop - Main shell loop
 * @prompt: The prompt to show, Enter string for
 * non-interractive mode
 * @data: Data of the shell
 */
void shell_loop(char *prompt, shell_info *data)
{
	char **args;
	int builtin, error_no;

	while (++(data->execution_count))
	{
		write(STDOUT_FILENO, prompt, _strlen(prompt));
		read_line(data);

		if (data->cmdline[0] == '\0')
		{
			free(data->cmdline);
			continue;
		}

		args = tokenize_input(data->cmdline);
		data->cmd = args[0];
		data->args = args;
		builtin = error_no = is_builtin(data);

		if (builtin == -1)
			error_no = exec_command(args);

		if (error_no != 0)
			print_error(error_no, data);
		free_program_data(data);
	}
}
