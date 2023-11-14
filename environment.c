#include "shell.h"

/**
 * compare_env_name - compares environment variable names
 * with the name passed.
 * @env_var: name of the environment variable
 * @name: name passed
 *
 * Return: 0 if they are not equal. Another value if they are.
 */
int compare_env_name(const char *env_var, const char *name)
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
 * @environ: environment variable
 *
 * Return: value of the environment variable if found.
 * Otherwise, returns NULL.
 */
char *get_environment_variable(const char *name, char **environ)
{
	char *ptr_env;
	int i, move;

	/* Initialize ptr_env value */
	ptr_env = NULL;
	move = 0;
	/* Compare all environment variables */
	/* environ is declared in the header file */
	for (i = 0; environ[i]; i++)
	{
		/* If name and env are equal */
		move = compare_env_name(environ[i], name);
		if (move)
		{
			ptr_env = environ[i];
			break;
		}
	}

	return (ptr_env + move);
}

/**
 * print_environment - prints the environment variables
 *
 * @shell_data: data relevant.
 * Return: 1 on success.
 */
int print_environment(shell_data *shell_data)
{
	int i, j;

	for (i = 0; shell_data->environment[i]; i++)
	{

		for (j = 0; shell_data->environment[i][j]; j++)
			;

		write(STDOUT_FILENO, shell_data->environment[i], j);
		write(STDOUT_FILENO, "\n", 1);
	}
	shell_data->status = 0;

	return (1);
}
