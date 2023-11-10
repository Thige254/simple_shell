#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 * main - entry point
 *
 * Return: 0 on success, 1 on error
 */
int main(void)
{
	char *input;
	char **tokens;
	char *executable;

	while (1)
	{
		input = display_prompt();
		tokens = tokenize_input(input);

		/* Check for built-in commands */
		if (tokens != NULL && tokens[0] != NULL)
		{
			if (strcmp(tokens[0], "exit") == 0)
			{
				free(input);
				free(tokens);
				exit(0);
			}
			else if (strcmp(tokens[0], "env") == 0)
			{
				handle_env();
				free(input);
				free(tokens);
				continue; /* Skip the fork and wait for built-in commands */
			}
		}

		/* Search for the executable */
		executable = find_executable(tokens[0]);

		if (executable != NULL)
		{
			/* Fork and execute the command */
			pid_t child_pid = fork();
			if (child_pid == -1)
			{
				perror("fork");
				exit(1);
			}
			if (child_pid == 0)
			{
				/* Child process */
				if (execve(executable, tokens, NULL) == -1)
				{
					perror("execve");
				}
				exit(1);
			}
			else
			{
				/* Parent process */
				int status;
				wait(&status);
			}
		}
		else
		{
			/* Handle the case where the command doesn't exist */
			printf("%s: command not found\n", tokens[0]);
		}

		/* Free allocated memory */
		free(input);
		free(tokens);
	}

	return (0);
}
