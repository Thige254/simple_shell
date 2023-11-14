#include "shell.h"

/**
 * duplicate_info - duplicates information to create
 * a new environment variable or alias
 * @name: name (environment variable or alias)
 * @value: value (environment variable or alias)
 *
 * Return: new environment variable or alias.
 */
char *duplicate_info(char *name, char *value)
{
	char *new;
	int len_name, len_value, len;

	len_name = _strlen(name);
	len_value = _strlen(value);
	len = len_name + len_value + 2;
	new = malloc(sizeof(char) * (len));
	_strcpy(new, name);
	_strcat(new, "=");
	_strcat(new, value);
	_strcat(new, "\0");

	return (new);
}

/**
 * set_environment_variable - sets an environment variable
 *
 * @name: name of the environment variable
 * @value: value of the environment variable
 * @shell_data: data structure (environ)
 * Return: no return
 */
void set_environment_variable(char *name, char *value, shell_data *shell_data)
{
	int i;
	char *var_env, *name_env;

	for (i = 0; shell_data->environment[i]; i++)
	{
		var_env = _strdup(shell_data->environment[i]);
		name_env = _strtok(var_env, "=");
		if (_strcmp(name_env, name) == 0)
		{
			free(shell_data->environment[i]);
			shell_data->environment[i] = duplicate_info(name_env, value);
			free(var_env);
			return;
		}
		free(var_env);
	}

	shell_data->environment = _reallocdp(shell_data->environment,
	i, sizeof(char *) * (i + 2));
	shell_data->environment[i] = duplicate_info(name, value);
	shell_data->environment[i + 1] = NULL;
}

/**
 * _set_environment - compares environment variable names
 * with the name passed.
 * @shell_data: data relevant (environment name and environment value)
 *
 * Return: 1 on success.
 */
int _set_environment(shell_data *shell_data)
{
	if (shell_data->arguments[1] == NULL || shell_data->arguments[2] == NULL)
	{
		get_error(shell_data, -1);
		return (1);
	}

	set_environment_variable(shell_data->arguments[1],
	shell_data->arguments[2], shell_data);

	return (1);
}

/**
 * _unset_environment - deletes an environment variable
 *
 * @shell_data: data relevant (environment name)
 *
 * Return: 1 on success.
 */
int _unset_environment(shell_data *shell_data)
{
	char **realloc_environment;
	char *var_env, *name_env;
	int i, j, k;

	if (shell_data->arguments[1] == NULL)
	{
		get_error(shell_data, -1);
		return (1);
	}
	k = -1;
	for (i = 0; shell_data->environment[i]; i++)
	{
		var_env = _strdup(shell_data->environment[i]);
		name_env = _strtok(var_env, "=");
		if (_strcmp(name_env, shell_data->arguments[1]) == 0)
		{
			k = i;
		}
		free(var_env);
	}
	if (k == -1)
	{
		get_error(shell_data, -1);
		return (1);
	}
	realloc_environment = malloc(sizeof(char *) * (i));
	for (i = j = 0; shell_data->environment[i]; i++)
	{
		if (i != k)
		{
			realloc_environment[j] = shell_data->environment[i];
			j++;
		}
	}
	realloc_environment[j] = NULL;
	free(shell_data->environment[k]);
	free(shell_data->environment);
	shell_data->environment = realloc_environment;
	return (1);
}
