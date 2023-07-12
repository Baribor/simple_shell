#include "shell.h"
/**
 * read_line - reads input from standard input
 * Return: returns the line read
 */
char *read_line(void)
{
	char *line = NULL;
	size_t bufsize = 0;
	ssize_t bytes_read = getline(&line, &bufsize, stdin);

	if (bytes_read == -1)
	{
		if(is_eof(0))
			handle_eof();
		else
		{
			perror("read line");
			exit(EXIT_FAILURE);
		}
	}
	if (bytes_read > 0 && line[bytes_read - 1] == '\n')
		line[bytes_read - 1] = '\0';
	return (line);
}
int is_eof(int fd)
{
	char c;
	ssize_t bytes = read(fd, &c, 1);

	if (bytes == 0)
		return (1);
	else
		return (0);
}
void handle_eof(void)
{
	char new_line = '\n';

	write(1, &new_line, 1);
	exit(EXIT_SUCCESS);
}
