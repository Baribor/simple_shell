#include "shell.h"
char *_getenv(const char *name);

int check_exec(char *args)
{
	if (access(args, X_OK) == 0 && access(args, F_OK) == 0)
		return (1);
	return (0);
}
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
		
		if (access(cmd_path, X_OK) == 0 && access(cmd_path, F_OK) == 0)
			return (cmd_path);
		free(cmd_path);
		dir = strtok(NULL, ":");
	}
	free(path);
	return (NULL);
}
char *_getenv(const char *name)
{
	extern char **environ;
	size_t name_len = _strlen(name);
	int i;

	for (i = 0; environ[i] != NULL; i++)
	{
		if (_strncmp(environ[i], name, name_len) == 0 && environ[i][name_len] == '=')
		{
			char *value = &environ[i][name_len + 1];
			return (value);
		}
	}
	return (NULL);
}

void exec_command(char **args)
{
	pid_t pid, wpid;
	int status;

	if (check_exec(args[0]) == 1)
	{
		pid = fork();
		if (pid < 0)
		{
			perror("fork error");
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
		{
			if (execve(args[0], args, NULL) == -1)
				perror("execve error");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		char *cmd_path = handle_path(args[0]);

		if (cmd_path != NULL)
		{
			args[0] = cmd_path;
			pid = fork();
			
			if (pid < 0)
			{
				perror("fork error");
				exit(EXIT_FAILURE);
			}
			else if (pid == 0)
			{
				if (execve(cmd_path, args, NULL) == -1)
					perror("execve error");
				exit(EXIT_FAILURE);
			}
			free(cmd_path);
		}
		else
		{
			perror("Error: Executable file not found.\n");
			exit(EXIT_FAILURE);
		}
	}
	if (pid > 0)
	{
		do
		{
			wpid = waitpid(pid, &status, WUNTRACED);
			if (wpid == -1)
			{
				perror("waitpid error");
				exit(EXIT_FAILURE);
			}
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
}
