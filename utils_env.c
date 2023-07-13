#include "shell.h"

/**
 * _getenv - Gets the value of an environment variable
 * @name: The name of the environment bvariable
 * Return: The value of the environment variable
 */
char *_getenv(const char *name)
{
	size_t name_len = _strlen(name);
	char *value;
	int i;

	for (i = 0; environ[i] != NULL; i++)
	{
		if (_strncmp(environ[i], name, name_len) == 0 && environ[i][name_len] == '=')
		{
			value = &environ[i][name_len + 1];
			return (value);
		}
	}
	return (NULL);
}
