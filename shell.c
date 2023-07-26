#include "shell.h"

alias_list *al = NULL;
/**
 * main - Entry point of the shell.
 * @argc: Number of arguments
 * @argv: Values of the arguments passed.
 * Return: 0 if success.
 */
int main(int argc, char *argv[])
{
	char *prompt = "";
	shell_info data = {NULL};
	int file_fd = STDIN_FILENO;

	init_data(&data);
	data.name = argv[0];

	/*checks if arguments were given */
	if (argv[1] && argc > 1)
	{
		file_fd = open(argv[1], O_RDONLY);
		if (file_fd == -1)
		{
			perror("Error opening file");
			exit(EXIT_FAILURE);
		}
	}

	/* Check if the shell is in interractive mode */
	if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO) && argc == 1)
		prompt = PROMPT;

	shell_loop(prompt, &data, file_fd);

	if (file_fd != STDIN_FILENO)
		close(file_fd);
	return (0);
}
