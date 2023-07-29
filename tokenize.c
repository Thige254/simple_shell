#include "shell.h"

/**
 * tokenize_command - Tokenizes a command into arguments.
 * @line: The command read from stdin.
 * @tokens: An array of tokens/arguments.
 * @position: Position in the array of tokens/arguments.
 *
 * Return: A NULL-terminated array of strings.
 */
char **tokenize_command(char *line, char **tokens, int position)
{
	char *token = NULL;
	int bufsize_token = 64;

	token = strtok(line, " \t\r\n\a");
	while (token != NULL)
	{
		tokens[position] = token;
		position++;

		if (position >= bufsize_token)
		{
			bufsize_token += 64;
			tokens = realloc(tokens, bufsize_token * sizeof(char *));
			if (!tokens)
			{
				fprintf(stderr, "Allocation error\n");
				exit(EXIT_FAILURE);
			}
		}

		token = strtok(NULL, " \t\r\n\a");
	}

	tokens[position] = NULL;
	return (tokens);
}
