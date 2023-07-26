#include "shell.h"

/**
 * main - Entry point of the shell.
 * @argc: Number of arguments
 * @argv: Values of the arguments passed.
 * Return: 0 if success.
 */
int main(__attribute((unused)) int argc, __attribute((unused)) char *argv[])
{
	shell_info data = {NULL};
	int file_fd = STDIN_FILENO;

	signal(SIGINT, handle_sigint);

	init_data(&data);
	data.name = argv[0];
<<<<<<< HEAD

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
=======

	shell_loop(&data);
>>>>>>> 55388401bd140d0fd662f7274b7a46c0b1af5caa
	return (0);
}
