#include "shell.h"

/**
 * tokenize_input - Splits a string into tokens
 * @line: The string to split
 * Return: An array of string tokens
 */
char **tokenize_input(char *line)
{
	/* allocates memory for array of strings */
	char **tokens = malloc(MAX_TOKENS * sizeof(char *));
	char *token;
	int count = 0, bufsize = MAX_TOKENS;

	if (!tokens) /*if dynamic allocation was unsuccessful */
	{
		perror("Allocation error");
		exit(EXIT_FAILURE);
	}
	token = strtok(line, DELIM); /*splits line int strings */

	while (token != NULL)
	{
		tokens[count] = token;
		count++;
		if (count >= bufsize)
		{
			bufsize += MAX_TOKENS;
			tokens = realloc(tokens, bufsize * sizeof(char *));
			if (!tokens)
			{
				perror("Reallocation error");
				exit(EXIT_FAILURE);
			}
		}
		token = strtok(NULL, DELIM);
	}
	tokens[count] = NULL;
	return (tokens);
}
