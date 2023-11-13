#include "shell.h"

/**
 * compare_env_names - compares environment variable names
 * with the name passed.
 * @env_var: environment variable name
 * @name: name passed
 *
 * Return: 0 if they are not equal. Another value if they are.
 */
int compare_env_names(const char *env_var, const char *name)
{
	int i;

	for (i = 0; env_var[i] != '='; i++)
	{
		if (env_var[i] != name[i])
		{
			return (0);
		}
	}

	return (i + 1);
}

/**
 * get_environment_variable - get an environment variable
 * @name: name of the environment variable
 * @_environ: environment variable array
 *
 * Return: value of the environment variable if found.
 * In other case, returns NULL.
 */
char *get_environment_variable(const char *name, char **_environ)
{
	char *ptr_env;
	int i, move;

	/* Initialize ptr_env value */
	ptr_env = NULL;
	move = 0;

	/* Compare all environment variables */
	for (i = 0; _environ[i]; i++)
	{
		/* If name and env_var are equal */
		move = compare_env_names(_environ[i], name);
		if (move)
		{
			ptr_env = _environ[i];
			break;
		}
	}

	return (ptr_env + move);
}

/**
 * print_environment_variables - prints the environment variables
 *
 * @datash: data relevant.
 * Return: 1 on success.
 */
int print_environment_variables(data_shell *datash)
{
	int i, j;

	for (i = 0; datash->_environ[i]; i++)
	{
		for (j = 0; datash->_environ[i][j]; j++)
			;

		write(STDOUT_FILENO, datash->_environ[i], j);
		write(STDOUT_FILENO, "\n", 1);
	}

	datash->status = 0;
	return (1);
}
