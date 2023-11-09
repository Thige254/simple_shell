#include "shell.h"

/**
 * tokenize_input - Tokenize user input into a command and arguments.
 * @input: The user input as a string.
 * Return: an array of strings where the first element is the command
 * and the rest are arguments.
 */
char **tokenize_input(char *input)
{
	char **tokens = NULL;
	char *token = NULL;
	int token_count = 0;

	if (input)
	{
		tokens = malloc(sizeof(char *));
		if (!tokens)
		{
			perror("Malloc error");
		}

		token = strtok(input, " \t\n");

		while (token)
		{
			tokens = realloc(tokens, sizeof(char *) * (token_count + 2));
			if (!tokens)
			{
				perror("Realloc error");
			}
			tokens[token_count] = token;
			tokens[token_count + 1] = NULL;
			token_count++;
			token = strtok(NULL, " \t\n");
		}
	}
	return (tokens);
}
