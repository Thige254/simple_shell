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
