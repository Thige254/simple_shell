#define _GNU_SOURCE
#include <stdlib.h>
#include "shell.h"

/**
 * _getenv - Retrieves the environment variable from the
 * global environ variable.
 * @name: The name of the environment variable.
 *
 * Return: The value of the environment variable or NULL if it does not exist.
 */
char **_getenv(char *name)
{
	int i;
	char **env;

	for (i = 0; environ[i]; i++)
	{
		env = _strtok(environ[i], "=");
		if (_strcmp(env[0], name) == 0)
			return (env);
		free(env);
	}

	return (NULL);
}

/**
 * free_env - Frees the environment variables.
 *
 * Return: void
 */
void free_env(void)
{
	int i;

	for (i = 0; environ[i]; i++)
		free(environ[i]);

	free(environ);
}

/**
 * _setenv - Sets the environment variable in the global environ variable.
 * @name: The name of the environment variable.
 * @value: The value of the environment variable.
 * @overwrite: If the environment variable exists, overwrite it if non-zero.
 *
 * Return: void
 */
void _setenv(const char *name, const char *value, int overwrite)
{
	char **env;
	char *new_env;

	env = _getenv((char *)name);

	if (env || overwrite)
	{
		new_env = malloc(_strlen(name) + _strlen(value) + 2);
		if (!new_env)
			return;
		_strcpy(new_env, name);
		_strcat(new_env, "=");
		_strcat(new_env, value);

		if (env)
			*env = new_env;
		else
			environ = _add_to_double_ptr(environ, new_env);
	}
}

/**
 * _unsetenv - Unsets the environment variable in the global environ variable.
 * @name: The name of the environment variable.
 *
 * Return: void
 */
void _unsetenv(const char *name)
{
	char **env;

	env = _getenv((char *)name);

	if (env)
		environ = _remove_from_double_ptr(environ, *env);
}
