#include "shell.h"

/**
 * handle_setenv - Handle the setenv command.
 * @info: Structure containing potential arguments.
 * @tokens: Array of strings containing command tokens.
 */
void handle_setenv(info_t *info, char **tokens)
{
	if (!tokens[1] || !tokens[2])
	{
		fprintf(stderr, "Usage: setenv VARIABLE VALUE\n");
		return;
	}

	_setenv(info, tokens[1], tokens[2]);
}

/**
 * handle_unsetenv - Handle the unsetenv command.
 * @info: Structure containing potential arguments.
 * @tokens: Array of strings containing command tokens.
 */
void handle_unsetenv(info_t *info, char **tokens)
{
	if (!tokens[1])
	{
		fprintf(stderr, "Usage: unsetenv VARIABLE\n");
		return;
	}

	_unsetenv(info, tokens[1]);
}
