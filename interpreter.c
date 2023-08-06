#include "shell.h"

int cd_builtin(char **args, char **front);
int exit_builtin(char **args, char **front);
int env_builtin(char **args, char **front);
int setenv_builtin(char **args, char **front);
int unsetenv_builtin(char **args, char **front);

builtin_t builtins[] = {
	{"cd", cd_builtin},
	{"exit", exit_builtin},
	{"env", env_builtin},
	{"setenv", setenv_builtin},
	{"unsetenv", unsetenv_builtin},
	{NULL, NULL}
};

/**
 * get_builtin - Retrieves a built-in function.
 * @s: The name of the built-in function to find.
 *
 * Return: If s does not match a built-in - NULL.
 *         Otherwise - a pointer to the function.
 */
int (*get_builtin(char *s))(char **args, char **front)
{
	int index;

	for (index = 0; builtins[index].name != NULL; index++)
	{
		if (_strcmp(s, builtins[index].name) == 0)
			return (builtins[index].func);
	}

	return (NULL);
}

/**
 * cd_builtin - Changes the current directory.
 * @args: An array of arguments.
 * @front: A double pointer to the beginning of args.
 *
 * Return: 0 if successful, 2 if it fails.
 */
int cd_builtin(char **args, char **front)
{
	(void)front;

	if (args[0] == NULL)
	{
		chdir(getenv("HOME"));
		return (0);
	}
	else if (chdir(args[0]) != 0)
	{
		perror("hsh");
		return (2);
	}

	return (0);
}

/**
 * exit_builtin - Exits the shell.
 * @args: An array of arguments.
 * @front: A double pointer to the beginning of args.
 *
 * Return: The status to exit the shell with.
 */
int exit_builtin(char **args, char **front)
{
	(void)args;
	(void)front;

	return (-EXIT);
}

/**
 * env_builtin - Prints the current environment.
 * @args: An array of arguments.
 * @front: A double pointer to the beginning of args.
 *
 * Return: 0.
 */
int env_builtin(char **args, char **front)
{
	print_env();

	return (0);
}

/**
 * setenv_builtin - Sets an environment variable.
 * @args: An array of arguments.
 * @front: A double pointer to the beginning of args.
 *
 * Return: 0 if successful, 2 if it fails.
 */
int setenv_builtin(char **args, char **front)
{
	if (args[0] == NULL || args[1] == NULL)
	{
		perror("hsh");
		return (2);
	}
	else
	{
		_setenv(args[0], args[1], 1);
		return (0);
	}
}

/**
 * unsetenv_builtin - Unsets an environment variable.
 * @args: An array of arguments.
 * @front: A double pointer to the beginning of args.
 *
 * Return: 0 if successful, 2 if it fails.
 */
int unsetenv_builtin(char **args, char **front)
{
	if (args[0] == NULL)
	{
		perror("hsh");
		return (2);
	}
	else
	{
		_unsetenv(args[0]);
		return (0);
	}
}
