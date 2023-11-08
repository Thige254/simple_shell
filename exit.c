#include "shell.h"
#include "exit.h"

/* Function to execute a command in a child process */
int exec_command(char *cmd);

/* Function to run the simple shell */
void run_shell(void);

/**
 * main - Entry point for the simple shell
 *
 * Return: Always 0
 */
int main(void)
{
	run_shell();
	return (0);
}

/* Function to execute a command in a child process */
int exec_command(char *cmd)
{
	pid_t child_pid;
	int status;
	char *token;
	int arg_index;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Fork failed");
		return (-1);
	}

	if (child_pid == 0)
	{
		char *cmd_args[64];
		cmd_args[0] = "/bin/sh";
		cmd_args[1] = "-c";

		arg_index = 2;

		token = strtok(cmd, " ");
		while (token != NULL)
		{
			cmd_args[arg_index] = token;
			token = strtok(NULL, " ");
			arg_index++;
		}

		cmd_args[arg_index] = NULL;

		/* Execute the command using /bin/sh -c */
		execve("/bin/sh", cmd_args, NULL);

		/* Handle execve failure */
		fprintf(stderr, "execve failed: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	else
	{
		wait(&status);
	}

	return (0);
}

/* Function to run the simple shell */
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

		/* Check for the "exit" command */
		if (strcmp(input, "exit") == 0)
		{
			exit_builtin();
		}

		/* Execute commands or handle errors */
		if (exec_command(input) == -1)
			fprintf(stderr, "Error: Command not found\n");

		free(input);
	}
}
