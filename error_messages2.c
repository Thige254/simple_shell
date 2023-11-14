#include "shell.h"

/**
 * environment_error_message - error message for env in get_env.
 * @shell_data: data relevant (counter, arguments)
 * Return: error message.
 */
char *environment_error_message(shell_data *shell_data)
{
	int length;
	char *error;
	char *line_number;
	char *msg;

	line_number = aux_itoa(shell_data->counter);
	msg = ": Unable to add/remove from environment\n";
	length = _strlen(shell_data->arguments[0]) + _strlen(line_number);
	length += _strlen(shell_data->args[0]) + _strlen(msg) + 4;
	error = malloc(sizeof(char) * (length + 1));
	if (error == 0)
	{
		free(error);
		free(line_number);
		return (NULL);
	}

	_strcpy(error, shell_data->arguments[0]);
	_strcat(error, ": ");
	_strcat(error, line_number);
	_strcat(error, ": ");
	_strcat(error, shell_data->args[0]);
	_strcat(error, msg);
	_strcat(error, "\0");
	free(line_number);

	return (error);
}

/**
 * path_error_message_126 - error message for path
 * and failure denied permission.
 * @shell_data: data relevant (counter, arguments).
 *
 * Return: The error string.
 */
char *path_error_message_126(shell_data *shell_data)
{
	int length;
	char *line_number;
	char *error;

	line_number = aux_itoa(shell_data->counter);
	length = _strlen(shell_data->arguments[0]) + _strlen(line_number);
	length += _strlen(shell_data->args[0]) + 24;
	error = malloc(sizeof(char) * (length + 1));
	if (error == 0)
	{
		free(error);
		free(line_number);
		return (NULL);
	}
	_strcpy(error, shell_data->arguments[0]);
	_strcat(error, ": ");
	_strcat(error, line_number);
	_strcat(error, ": ");
	_strcat(error, shell_data->args[0]);
	_strcat(error, ": Permission denied\n");
	_strcat(error, "\0");
	free(line_number);
	return (error);
}
