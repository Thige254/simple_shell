#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * handle_exit - Handles the "exit" built-in command.
 * @tokens: Array of strings representing the command and its arguments.
 *
 * Description:
 * This function checks if the command is "exit" and, if so, exits the shell.
 * It frees the memory allocated for tokens before exiting.
 * If "exit" is part of another command, it prints an error message.
 */
void handle_exit(char **tokens)
{
	/* Check if the command is "exit" */
	if (tokens != NULL && tokens[0] != NULL && strcmp(tokens[0], "exit") == 0)
	{
		free(tokens);
		exit(0);
	}
	else
	{
		/* Print an error message for other cases */
		fprintf(stderr, "Shell: command not found: %s\n", tokens[0]);
		/* Free the memory allocated for tokens */
		free(tokens);
		/* I will add more error handling / execute the command here */
	}
}
