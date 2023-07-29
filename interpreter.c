#include "shell.h"

char *read_command(void);
void shell_loop(void);
char *get_cmd_path(char *cmd);

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
	return (line);
}

/**
 * shell_loop - main loop. Its where commands are read and executed.
 */
void shell_loop(void)
{
	char *line;
	char *cmd_path;
	pid_t pid;
	int status;

	do {
		write(STDOUT_FILENO, "> ", 2);
		line = read_command();
		line[strcspn(line, "\n")] = 0; /* Strip the newline char */

		pid = fork();

if (pid == 0)
{
	/* Child process */
	char *argv[2];

	cmd_path = get_cmd_path(line);
	if (cmd_path == NULL)
	{
		write(STDERR_FILENO, line, strlen(line));
		write(STDERR_FILENO, ": not found\n", 12);
		exit(EXIT_FAILURE);
	}
	argv[0] = cmd_path;
	argv[1] = NULL;
	if (execve(cmd_path, argv, environ) == -1)
	{
		write(STDERR_FILENO, line, strlen(line));
		write(STDERR_FILENO, ": not found\n", 12);
		exit(EXIT_FAILURE);
	}
}

		else if (pid < 0)
		{
			/* Error forking */
			perror("hsh");
		}
		else
		{
			/* Parent process */
			do {
				waitpid(pid, &status, WUNTRACED);
			} while (!WIFEXITED(status) && !WIFSIGNALED(status));
		}

		free(line);
	} while (1);
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
