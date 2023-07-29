#include "shell.h"

/**
 * read_command - Reads a command from stdin and tokenizes it into arguments.
 *
 * Return: A NULL-terminated array of strings.
 * On erro function will print an error message
 * & exit with a status of EXIT_FAILURE.
 */
char **read_command(void)
{
	char *line = NULL;
	size_t bufsize = 0;
	char **tokens = NULL;
	int position = 0;

	if (getline(&line, &bufsize, stdin) == -1)
	{
		if (feof(stdin))
		{
			write(STDOUT_FILENO, "\n", 1);
			exit(EXIT_SUCCESS);
		}
		else
		{
			perror("readline");
			exit(EXIT_FAILURE);
		}
	}

	tokens = malloc(64 * sizeof(char *));
	if (!tokens)
	{
		fprintf(stderr, "Allocation error\n");
		exit(EXIT_FAILURE);
	}

	tokens = tokenize_command(line, tokens, position);

	return (tokens);
}
