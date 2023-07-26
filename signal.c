#include "shell.h"

/**
 * handle_sigint - handles the signal int
 * @signal: The signal code
 * Return: void
 */
void handle_sigint(int signal)
{
	if (signal == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		show_prompt();
		fflush(stdout);
	}
}
