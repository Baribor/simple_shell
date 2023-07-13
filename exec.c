#include "shell.h"

/**
 * handle_path - Finds an executable in the system PATH
 * @args: command name
 * Return: Full path of the executable
 */
char *handle_path(char *args)
{
	char *path = strdup(_getenv("PATH"));
	char *dir = strtok(path, ":");
	char *cmd_path;
	size_t dir_len, args_len, path_len;

	while (dir != NULL)
	{
		dir_len = _strlen(dir);
		args_len = _strlen(args);
		path_len = dir_len + args_len + 2;

		cmd_path = malloc(path_len);
		if (cmd_path == NULL)
		{
			perror("Memory allocation error");
			exit(EXIT_FAILURE);
		}
		_strcpy(cmd_path, dir);
		_strcat(cmd_path, "/");
		_strcat(cmd_path, args);

		if (check_exec(cmd_path))
			return (cmd_path);
		free(cmd_path);
		dir = strtok(NULL, ":");
	}
	free(path);
	return (NULL);
}

/**
 * execute - Main external commnand handler
 * @args: Arguments passed
 * Return: Void
 */
void execute(char **args)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid < 0)
	{
		perror("fork error");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		if (execve(args[0], args, environ) == -1)
			perror("execve error");
		exit(EXIT_FAILURE);
	}

	if (pid > 0)
	{
		waitpid(pid, &status, WUNTRACED);
		if (WIFEXITED(status))
			errno = WEXITSTATUS(status);
	}
}

/**
 * exec_command - Handles external commands
 * @args: Arguments passed
 * Return: void
 */
void exec_command(char **args)
{

	/* If a full path to an executable is entered */
	if (check_exec(args[0]) == 1)
	{
		execute(args);
	}
	else
	{
		/* Try to get the full path using the system PATH env variable */
		char *cmd_path = handle_path(args[0]);

		if (cmd_path != NULL)
		{
			args[0] = cmd_path;
			execute(args);
		}
		else
		{
			perror("Error: Executable file not found.\n");
			exit(EXIT_FAILURE);
		}
	}
}
