#include "shell.h"
#include <stdlib.h>
#include <string.h>

/**
 * handle_exit - Handles the "exit" built-in command.
 * @tokens: Array of strings representing the command and its arguments.
 *
 * Description:
 * This function checks if the command is "exit" and, if so, exits the shell.
 * It frees the memory allocated for tokens before exiting.
 */
void handle_exit(char **tokens)
{
	/* Check if the command is "exit" */
	if (tokens != NULL && tokens[0] != NULL && strcmp(tokens[0], "exit") == 0)
	{
		free(tokens);
		exit(0);
	}
}
