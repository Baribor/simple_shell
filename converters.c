#include "shell.h"

/**
 * number_to_string - Converts a number to string
 * @buf: Buffer to store the string version
 * of the number
 * @num: The number to convert
 * Return: Void
 */
void number_to_string(char *buf, int num)
{
	int i = 0;

	while (num)
	{
		buf[i++] = '0' + (num % 10);
		num /= 10;
	}
	reverse_string(buf);
}

/**
 * reverse_string - Reverses a string in place
 * @str: string to be reversed
 * Retunr: Void
 */
void reverse_string(char *str)
{
	int len = _strlen(str), i = 0;
	char *dup = malloc(sizeof(char) * len + 1);

	_strcpy(dup, str);

	while (--len >= 0)
	{
		str[i++] = dup[len];
	}
	free(dup);
}
