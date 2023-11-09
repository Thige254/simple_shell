#include "shell.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

/**
 * main - entry point
 * @ac: arg count
 * @av: arg vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int ac, char **av)
{
	char *input;
	char **tokens;

	while (1)
	{
		input = display_prompt();
		tokens = tokenize_input(input);

		/* Search for the executable */
		char *executable = find_executable(tokens[0]);

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
				execve(executable, tokens, NULL);
				perror("execve");  // If execve fails
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
