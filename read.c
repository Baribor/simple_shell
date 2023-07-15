#include "shell.h"
/**
 * read_line - reads input from standard input
 * @data: Program data
 * Return: returns the line read
 */
void read_line(shell_info *data)
{
	char *line = NULL;
	size_t bufsize = 0;
	ssize_t bytes_read = getline(&line, &bufsize, stdin);

	if (bytes_read == -1)
	{
		free(line);
		if (is_eof(STDIN_FILENO))
			handle_eof();
		else
		{
			perror("read line");
			exit(EXIT_FAILURE);
		}
	}
	if (bytes_read > 0 && line[bytes_read - 1] == '\n')
		line[bytes_read - 1] = '\0';
	data->cmdline = line;
}

/**
 * is_eof - Check for EOF
 * @fd: File descriptor
 * Return: 1 if EOF else 0
 */
int is_eof(int fd)
{
	char c;
	ssize_t bytes = read(fd, &c, 1);

	return (bytes == 0);
}

/**
 * handle_eof - EOF handler for non_interractive mode
 * Return: void
 */
void handle_eof(void)
{
	exit(errno);
}
