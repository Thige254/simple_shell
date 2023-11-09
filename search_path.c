#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno>


/**
 * find_executable - find the executables of arguments.
 * @command: The user command string.
 * Return: Return NULL if the executable is not found.
 */
char *find_executable(char *command)
{
	char *path = getenv("PATH");
	if (path == NULL)
	{
		return (NULL);
	}

	char *path_copy = strdup(path);
	if (path_copy == NULL)
	{
		perror("strdup");
		return (NULL);
	}

	char *token = strtok(path_copy, ":");
	while (token != NULL)
	{
		/* Check if the executable exists in this directory */
		char *full_path = malloc(strlen(token) + strlen(command) + 2);
		/*+2 for '/' and null terminator */
		if (full_path == NULL)
		{
			perror("malloc");
			return (NULL);
		}
		sprintf(full_path, "%s/%s", token, command);

		if (access(full_path, X_OK) == 0)
		{
			free(path_copy);
			return (full_path);
		}
		free(full_path);

		token = strtok(NULL, ":");
	}

	free(path_copy);
	return (NULL); /* Return NULL if the executable is not found */
}
