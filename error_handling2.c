#include "shell.h"
#include "string_conversions.c"

/**
 * handle_env_error - Error message for env command in get_env.
 * @shell_data: Shell data structure (counter, arguments)
 * Return: Error message.
 */
char *handle_env_error(data_shell *shell_data)
{
	int length;
	char *error;
	char *line_str;
	char *msg;

	line_str = _custom_itoa(shell_data->counter);
	msg = ": Unable to add/remove from environment\n";
	length = _custom_strlen(shell_data->av[0]) + _custom_strlen(line_str);
	length += _custom_strlen(shell_data->args[0]) + _custom_strlen(msg) + 4;
	error = malloc(sizeof(char) * (length + 1));

	if (error == 0)
	{
		free(error);
		free(line_str);
		return (NULL);
	}

	_custom_strcpy(error, shell_data->av[0]);
	_custom_strcat(error, ": ");
	_custom_strcat(error, line_str);
	_custom_strcat(error, ": ");
	_custom_strcat(error, shell_data->args[0]);
	_custom_strcat(error, msg);
	_custom_strcat(error, "\0");
	free(line_str);

	return (error);
}

/**
 * handle_permission_error - Error message for permission denied in path.
 * @shell_data: Shell data structure (counter, arguments).
 *
 * Return: The error string.
 */
char *handle_permission_error(data_shell *shell_data)
{
	int length;
	char *line_str;
	char *error;

	line_str = _custom_itoa(shell_data->counter);
	length = _custom_strlen(shell_data->av[0]) + _custom_strlen(line_str);
	length += _custom_strlen(shell_data->args[0]) + 24;
	error = malloc(sizeof(char) * (length + 1));

	if (error == 0)
	{
		free(error);
		free(line_str);
		return (NULL);
	}
	_custom_strcpy(error, shell_data->av[0]);
	_custom_strcat(error, ": ");
	_custom_strcat(error, line_str);
	_custom_strcat(error, ": ");
	_custom_strcat(error, shell_data->args[0]);
	_custom_strcat(error, ": Permission denied\n");
	_custom_strcat(error, "\0");
	free(line_str);
	return (error);
}
