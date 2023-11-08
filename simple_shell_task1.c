#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 1024
/**
 * run_shell - Run the simple shell
 *
 * Description: Display a prompt, read user input, and execute commands.
 */
void run_shell(void)
{
	char *input = NULL;
	size_t bufsize = 0;

	while (1)
	{
		printf("#cisfun$ ");

		if (getline(&input, &bufsize, stdin) == -1)
		{
			if (isatty(STDIN_FILENO))
				putchar('\n');
			free(input);
			exit(EXIT_SUCCESS);
		}

		/* Remove the trailing newline character from input */
		if (input[strlen(input) - 1] == '\n')
			input[strlen(input) - 1] = '\0';

		/* Execute commands or handle errors */
		if (exec_command(input) == -1)
			perror("Error");

		free(input);
	}
}
/**
 * exec_command - Execute a command in a child process
 * @cmd: The command to execute
 *
 * Return: 0 on success, -1 on failure
 */

int exec_command(char *cmd)
{
	pid_t child_pid;
	int status;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Fork failed");
		return (-1);
	}
	if (child_pid == 0)
	{
		if (execve(cmd, (char *const[])
		{cmd, NULL}, NULL) == -1)
		{
			return (-1);
		}
	}
	else
	{
		wait(&status);
	}
	return (0);
}
/**
 * main - Entry point for the simple shell
 *
 * Return: Always returns 0
 */

int main(void)
{
	run_shell();
	return (0);
}
