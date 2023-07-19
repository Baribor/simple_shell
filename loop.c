#include "shell.h"

/**
 * run_command - Runs a single command
 * @data: Program data
 * Return: void
 */
void run_command(shell_info *data)
{
	int builtin, error_no;

	tokenize_input(data);

	builtin = error_no = is_builtin(data);

	if (builtin == NOT_BUILTIN)
		error_no = exec_command(data);

	if (error_no != EXIT_SUCCESS)
		print_error(data);

	/* Free the data for the current command */
	free_program_data(data);
}

/**
 * shell_loop - Main shell loop
 * @prompt: The prompt to show, Enter string for
 * non-interractive mode
 * @data: Data of the shell
 */
void shell_loop(char *prompt, shell_info *data)
{
	ssize_t cmd_length, i;

	while (++(data->execution_count))
	{
		write(STDOUT_FILENO, prompt, _strlen(prompt));
		cmd_length = read_line(data);

		if (cmd_length == 0)
			continue;

		build_command_list(data);

		for (i = 0; data->cmdlist[i]; ++i)
		{
			data->cmd = data->cmdlist[i];
			if (check_comment(data))
			{
				if (!data->cmd[0])
					free_program_data(data);
				else
					run_command(data);
				break;
			}

			run_command(data);
		}

		/* Free the command list */
		free_array_of_pointers(data->cmdlist);
	}
}
