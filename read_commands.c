#include "shell.h"
/**
 * read_command - read a command from stdin
 *
 * Return: pointer to the command read
 */


char *read_command(void)
{
	char *line = NULL;
	size_t len = 0;

	getline(&line, &len, stdin);
	return (line);
}
