#include "shell.h"
/**
 * read_line - reads input from standard input
 * @data: Program data
 * Return: returns the line read
 */
ssize_t read_line(shell_info *data)
{
	char line[BUF_SIZE] = {'\0'};
	ssize_t bytes_read;
	static char *commands[MAX_TOKENS] = {NULL};
	int i = 0;

	if (commands[0] == NULL)
	{
		bytes_read = read(STDIN_FILENO, line, BUF_SIZE);

		/* Check for EOF */
		if (bytes_read == 0)
		{
			free_program_data(data);
			exit(errno);
		}

		/* Split input into lines of command if needed */
		commands[i] = _strdup(_strtok(line, "\n"));
		while (commands[i])
			commands[++i] = _strdup(_strtok(NULL, "\n"));
	}

	data->cmdline = commands[0];
	if (commands[0])
		data->cmdline = expand_variables(_strtrim(commands[0]), data);

	/**
	 * Shift the commands array so the first index
	 * can point to the next command.
	 */
	for (i = 0; commands[i]; i++)
	{
		commands[i] = commands[i + 1];
	}

	return (data->cmdline ? _strlen(data->cmdline) : 0);
}
