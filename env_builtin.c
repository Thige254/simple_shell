#include "shell.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * handle_env - Handles the "env" built-in command.
 * Note: Assumes that environ is declared in the included header file.
 */
void handle_env(void)
{
	/* Access the external environment variables */
	char **env = environ;
	while (*env)
	{
		printf("%s\n", *env);
		env++;
	}
}
