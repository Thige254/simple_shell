#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024

/* Function to execute a command in a child process */
int exec_command(char *cmd);

/* Function to run the simple shell */
/* Function to run the simple shell */
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
			free(input); /* Free memory in both success and error cases*/
			exit(EXIT_SUCCESS);
		}

		/* Remove the trailing newline character from input */
		if (input[strlen(input) - 1] == '\n')
			input[strlen(input) - 1] = '\0';

		/* Execute commands or handle errors */
		if (exec_command(input) == -1)
		/*  Print a specific error message*/
			fprintf(stderr, "Error: Command not found\n");

		free(input); /* Free memory in both success and error cases*/
	}
}

/* Function to execute a command in a child process */
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
		char *cmd_args[2];
		cmd_args[0] = cmd;
		cmd_args[1] = NULL;

		if (execve(cmd, cmd_args, NULL) == -1)
		{
			perror("execve failed");
			exit(EXIT_FAILURE); /* Exit the child process with failure status*/
		}
	}
	else
	{
		wait(&status);
	}

	return (0);
}
