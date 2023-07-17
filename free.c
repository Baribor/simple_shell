#include "shell.h"

/**
 * free_array_of_pointers - Frees a double pointer
 * @arr: The memory area to free
 * Return: void
 */
void free_array_of_pointers(char **arr)
{
	int i;

	if (!arr)
		return;

	for (i = 0; arr[i]; i++)
	{
		free(arr[i]);
	}
	free(arr);
}

/**
 * free_program_data - Frees the program data
 * @data: Program data
 * Return: void
 */
void free_program_data(shell_info *data)
{
	if (data->args)
		free_array_of_pointers(data->args);
	if (data->cmdline)
		free(data->cmdline);

	data->args = NULL;
	data->cmdline = NULL;
}
