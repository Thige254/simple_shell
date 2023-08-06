#include "shell.h"

/**
 * read_command - Read a command from stdin.
 *
 * Return: A pointer to the command read.
 */
char *read_command(void)
{
	char *line = NULL;
	size_t bufsize = 0;

	if (getline(&line, &bufsize, stdin) == -1)
	{
		if (feof(stdin))
		{
			write(STDOUT_FILENO, "\n", 1);
			exit(EXIT_SUCCESS);
		}
		else
		{
			perror("readline");
			exit(EXIT_FAILURE);
		}
	}
	/* Replace newline with null character */
	line[strlen(line) - 1] = '\0';
	return (line);
}

/**
 * get_cmd_path - Finds the full path of a command.
 * @cmd: The name of the command.
 *
 * Return: The full path of the command,
 * NULL if the command not found.
 */
char *get_cmd_path(char *cmd)
{
	char *path = getenv("PATH");
	char *path_copy = strdup(path);
	char *token = strtok(path_copy, ":");
	char *cmd_path = malloc(strlen(cmd) + strlen(path) + 2);
	struct stat buf;

	while (token != NULL)
	{
		strcpy(cmd_path, token);
		strcat(cmd_path, "/");
		strcat(cmd_path, cmd);

		if (stat(cmd_path, &buf) == 0)
		{
			free(path_copy);
			return (cmd_path);
		}
		token = strtok(NULL, ":");
	}

	free(cmd_path);
	free(path_copy);
	return (NULL);
}

/**
 * shell_loop - Main loop for the shell
 *
 */
void shell_loop(void)
{
	char *line;
	char *command;
	pid_t child_pid;
	int status;

	while (1)
	{
		printf("$ ");
		line = read_command();
		command = get_cmd_path(line);

		if (command == NULL)
		{
			fprintf(stderr, "%s: command not found\n", line);
			free(line);
			continue;
		}

		child_pid = fork();
		if (child_pid == -1)
		{
			perror("Error:");
			free(line);
			free(command);
			continue;
		}

		if (child_pid == 0)
		{
			/* Child process */
			char *argv[2];
			argv[0] = command;
			argv[1] = NULL;
			if (execve(command, argv, NULL) == -1)
			{
				perror("Error:");
			}
			exit(EXIT_FAILURE);
		}
		else
		{
			/* Parent process */
			wait(&status);
		}

		free(line);
		free(command);
	}
}
