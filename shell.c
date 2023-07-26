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

	signal(SIGINT, handle_sigint);

	init_data(&data);
	data.name = argv[0];

	shell_loop(&data);
	return (0);
}
