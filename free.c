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
		arr[i] = NULL;
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

/**
 * free_all_data - Frees all program data
 * @data: Program data
 * Return: void
 */
void free_all_data(shell_info *data)
{
	if (data->logic_data->operands)
		free_array_of_pointers(data->logic_data->operands);

	if (data->cmdlist)
		free_array_of_pointers(data->cmdlist);

	free_program_data(data);
}
