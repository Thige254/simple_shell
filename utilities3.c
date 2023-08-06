#include "shell.h"

/**
 * remove_comments - Removes any comments within a command string.
 * @str: The command string to parse.
 */
void remove_comments(char *str)
{
	while (*str)
	{
		if (*str == '#')
		{
			*str = '\0';
			return;
		}
		str++;
	}
}

/**
 * handle_line - Handles a command line input by removing comments,
 *               replacing variables, and handling the "exit" builtin.
 * @line: The command line to handle.
 * @line_size: The size of the command line.
 *
 * Return: If an error occurs - an error code.
 *         Otherwise - 0.
 */
int handle_line(char **line, size_t line_size)
{
	int ret;

	remove_comments(*line);
	variable_replacement(line, NULL);

	if (_strncmp(*line, "exit", 4) == 0)
	{
		free(*line);
		return (-EXIT);
	}

	return (0);
}

/**
 * handle_args - Tokenizes a line into arguments and then
 *               calls a function to execute the command.
 * @exe_ret: The return value of the last executed command.
 *
 * Return: If an error occurs - an error code.
 *         If "exit" builtin is called - EXIT.
 *         If end of file is encountered - END_OF_FILE.
 *         Otherwise - 0.
 */
int handle_args(int *exe_ret)
{
	ssize_t b_read;
	size_t line_size = 0;
	char *line = NULL;
	char **args, **front;
	int ret;

	b_read = getline(&line, &line_size, stdin);
	if (b_read == -1)
	{
		free(line);
		return (END_OF_FILE);
	}

	ret = handle_line(&line, line_size);
	if (ret)
		return (ret);

	args = _strtok(line, " ");
	if (!args)
	{
		free(line);
		return (0);
	}

	front = args;

	if (check_args(args) != 0)
	{
		*exe_ret = 2;
		free_args(args, front);
		return (*exe_ret);
	}

	*exe_ret = execute(args, front);

	free(front);
	return (0);
}
