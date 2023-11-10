#include "shell.h"

#define READ_BUF_SIZE 1024

/**
 * custom_getline - Reads a line from STDIN
 *
 * Return: The read line
 */
char *custom_getline(void)
{
	static char buffer[READ_BUF_SIZE];
	static size_t buf_index;
	static ssize_t bytes_read;

	ssize_t line_length = 0;
	char *line = NULL;

	if ((ssize_t)buf_index == 0 || (ssize_t)buf_index == bytes_read)
	{
		bytes_read = read(STDIN_FILENO, buffer, READ_BUF_SIZE);
		if (bytes_read <= 0)
		{
			if (line)
				free(line);
			return (NULL);
		}
		buf_index = 0;
	}

	while (buffer[buf_index] != '\n' && buffer[buf_index] != '\0')
	{
		buf_index++;
		line_length++;
	}

	if (buffer[buf_index] == '\n')
	{
		buffer[buf_index] = '\0';
		buf_index++;
	}

	line = malloc((line_length + 1) * sizeof(char));
	if (!line)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	strncpy(line, buffer + buf_index - line_length - 1, (size_t)line_length + 1);
	return (line);
}
