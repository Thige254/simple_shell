#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

char *find_executable(char *command)
{
	char *path = getenv("PATH");
	char *path_copy;
	char *token;
	char *full_path;

	if (path == NULL)
	{
		return (NULL);
	}

	path_copy = strdup(path);
	if (path_copy == NULL)
	{
		perror("strdup");
		return (NULL);
	}

	token = strtok(path_copy, ":");
	while (token != NULL)
	{
		full_path = malloc(strlen(token) + strlen(command) + 2);
		if (full_path == NULL)
		{
			perror("malloc");
			free(path_copy);
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
	return (NULL);
}
