#include "shell.h"

/**
* prompt_user - prints "$ " to the standard output
*/
void prompt_user(void)
{
	if (isatty(STDIN_FILENO))
		write(STDERR_FILENO, "$ ", 2);
}

/**
* read_command - reads a command from the standard input
* Return: the read command as a string
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
	return (line);
}

/**
* get_cmd_path - finds the absolute path of a command
* @cmd: command to find the path for
* Return: absolute path of the command
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
* exec_cmd - executes the command in a child process
* @command: command to execute
* @cmd_path: path of the command
*/
void exec_cmd(char *command, char *cmd_path)
{
	char *argv[2];
	pid_t child_pid;
	int status;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error");
		free(cmd_path);
		exit(1);
	}
	if (child_pid == 0)
	{
		argv[0] = command;
		argv[1] = NULL;
		if (execve(cmd_path, argv, NULL) == -1)
		{
			perror("Error");
		}
	}
	else
	{
		wait(&status);
	}
}

/**
* shell_loop - main loop of the shell
* It reads a command, tries to find the binary for the command
* and then forks a child process to execute the command
*/
void shell_loop(void)
{
	char *line;
	char *command;
	char *cmd_path;

	while (1)
	{
		prompt_user();
		line = read_command();
		if (strcmp(line, "\n") == 0)
		{
			free(line);
			continue;
		}
		command = strtok(line, "\n");
		cmd_path = get_cmd_path(command);
		if (cmd_path == NULL)
		{
			write(STDERR_FILENO, command, strlen(command));
			write(STDERR_FILENO, ": command not found\n", 20);
			free(line);
			continue;
		}
		exec_cmd(command, cmd_path);
		free(line);
		free(cmd_path);
	}
}
