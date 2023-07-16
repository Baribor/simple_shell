#include "shell.h"

/**
 * _print_err - Prints to the std error
 * @err: What to print
 * Return: Number of characters printed
 */
ssize_t _print_err(char *err)
{
	return (write(STDERR_FILENO, err, _strlen(err)));
}

/**
 * print_error - Handles error printing
 * @code: Error code
 * @data: Program data
 * Return: Void
 */
void print_error(int code, shell_info *data)
{
	char exec_count[10] = {'\0'};

	number_to_string(exec_count, data->execution_count);

	if (code == 126 || code == 127)
	{
		_print_err(data->name);
		_print_err(": ");
		_print_err(exec_count);
		_print_err(": ");
		_print_err(data->args[0]);
		_print_err(": ");
		_print_err(code == 127 ? "not found\n" : "Permission denied\n");
	}
}
