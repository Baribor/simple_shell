#include "shell.h"

/**
 * add_alias - creates or modifies alias
 * @name: name of the alias
 * @value: value of the alias
 */
void add_alias(char *name, char *value)
{
	alias_list *alias = al;
	alias_list *new;

	/* check if the alias already exists */
	while (alias != NULL)
	{
		if (_strcmp(alias->name, name) == 0)
		{
			free(alias->value);
			alias->value = _strdup(value);
			return;
		}
		alias = alias->next; /* moves to next node */
	}
	/* if alias doesnt exist, create a new one */
	new = malloc(sizeof(alias_list));
	new->name = _strdup(name);
	new->value = _strdup(value);
	new->next = al;
	al = new;
}

/**
 * print_alias - prints all or specified aliases
 * @var: pointer to head node
 * @names: array of strings of alias name
 */
void print_alias(alias_list *var, char **names)
{
	alias_list *alias = var;
	int i;

	while (alias != NULL)
	{
		if (names == NULL) /*print all aliases */
		{
			write(STDOUT_FILENO, alias->name, _strlen(alias->name));
			write(STDOUT_FILENO, "='", 2);
			write(STDOUT_FILENO, alias->value, _strlen(alias->value));
			write(STDOUT_FILENO, "'\n", 2);
		}
		else
		{
			for (i = 0; names[i]; i++)
			{
				if (_strcmp(alias->name, names[i]) == 0)
				{
					write(STDOUT_FILENO, alias->name, _strlen(alias->name));
					write(STDOUT_FILENO, "='", 2);
					write(STDOUT_FILENO, alias->value, _strlen(alias->value));
					write(STDOUT_FILENO, "'\n", 2);
					break;
				}
			}
		}
		alias = alias->next;
	}
}
/**
 * builtin_alias - creates or prints alias
 * @data: program data
 * Return: 0 if successful
 */
int builtin_alias(shell_info *data)
{
	char **args = data->args;
	char *name, *value;
	int i = 0;

	if (args[1] == NULL)
		print_alias(al, NULL);
	else if (args[2] == NULL)
		print_alias(al, &args[1]);
	else
	{
		i = 1;
		while (args[i] != NULL)
		{
			name = args[i];
			value = strchr(args[i], '=');
			if (value != NULL)
			{
				*value = '\0';
				value++;
				add_alias(name, value);
			}
			i++;
		}
	}
	return (0);
}
