#include "shell.h"

/**
 * shell_loop - Main shell loop
 * @prompt: The prompt to show, Enter string for
 * non-interractive mode
 * @data: Data of the shell
 */
void shell_loop(char *prompt, shell_info *data)
{
	int builtin, error_no;
	ssize_t cmd_length;

	while (++(data->execution_count))
	{
		write(STDOUT_FILENO, prompt, _strlen(prompt));
		cmd_length = read_line(data);

		if (cmd_length == 0)
			continue;

		tokenize_input(data);
		builtin = error_no = is_builtin(data);

		if (builtin == NOT_BUILTIN)
			error_no = exec_command(data);

		if (error_no != EXIT_SUCCESS)
			print_error(data);
		free_program_data(data);
	}
}
