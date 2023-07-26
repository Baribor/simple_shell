#include "shell.h"

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

	init_data(&data);
	data.name = argv[0];
	/* Not yet handling file input */
	(void)argv;

	/* Check if the shell is in interractive mode */
	if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO) && argc == 1)
		prompt = PROMPT;

	shell_loop(prompt, &data);
	return (0);
}
