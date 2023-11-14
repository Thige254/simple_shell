#include "shell.h"

/**
 * concatenate_cd_error - function that concatenates the message for cd error
 *
 * @shell_data: data relevant (directory)
 * @msg: message to print
 * @error: output message
 * @line_number: counter lines
 * Return: error message
 */
char *concatenate_cd_error(shell_data *shell_data,
char *msg, char *error, char *line_number)
{
	char *illegal_flag;

	_strcpy(error, shell_data->arguments[0]);
	_strcat(error, ": ");
	_strcat(error, line_number);
	_strcat(error, ": ");
	_strcat(error, shell_data->args[0]);
	_strcat(error, msg);
	if (shell_data->args[1][0] == '-')
	{
		illegal_flag = malloc(3);
		illegal_flag[0] = '-';
		illegal_flag[1] = shell_data->args[1][1];
		illegal_flag[2] = '\0';
		_strcat(error, illegal_flag);
		free(illegal_flag);
	}
	else
	{
		_strcat(error, shell_data->args[1]);
	}

	_strcat(error, "\n");
	_strcat(error, "\0");
	return (error);
}

/**
 * cd_error_message - error message for cd command in get_cd
 * @shell_data: data relevant (directory)
 * Return: Error message
 */
char *cd_error_message(shell_data *shell_data)
{
	int length, len_id;
	char *error, *line_number, *msg;

	line_number = aux_itoa(shell_data->counter);
	if (shell_data->args[1][0] == '-')
	{
		msg = ": Illegal option ";
		len_id = 2;
	}
	else
	{
		msg = ": can't cd to ";
		len_id = _strlen(shell_data->args[1]);
	}

	length = _strlen(shell_data->arguments[0]) + _strlen(shell_data->args[0]);
	length += _strlen(line_number) + _strlen(msg) + len_id + 5;
	error = malloc(sizeof(char) * (length + 1));

	if (error == 0)
	{
		free(line_number);
		return (NULL);
	}

	error = concatenate_cd_error(shell_data, msg, error, line_number);

	free(line_number);

	return (error);
}

/**
 * not_found_error_message - generic error message for command not found
 * @shell_data: data relevant (counter, arguments)
 * Return: Error message
 */
char *not_found_error_message(shell_data *shell_data)
{
	int length;
	char *error;
	char *line_number;

	line_number = aux_itoa(shell_data->counter);
	length = _strlen(shell_data->arguments[0]) + _strlen(line_number);
	length += _strlen(shell_data->args[0]) + 16;
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
	_strcat(error, ": not found\n");
	_strcat(error, "\0");
	free(line_number);
	return (error);
}

/**
 * exit_shell_error_message - generic error message for exit in get_exit
 * @shell_data: data relevant (counter, arguments)
 *
 * Return: Error message
 */
char *exit_shell_error_message(shell_data *shell_data)
{
	int length;
	char *error;
	char *line_number;

	line_number = aux_itoa(shell_data->counter);
	length = _strlen(shell_data->arguments[0]) + _strlen(line_number);
	length += _strlen(shell_data->args[0]) + _strlen(shell_data->args[1]) + 23;
	error = malloc(sizeof(char) * (length + 1));
	if (error == 0)
	{
		free(line_number);
		return (NULL);
	}
	_strcpy(error, shell_data->arguments[0]);
	_strcat(error, ": ");
	_strcat(error, line_number);
	_strcat(error, ": ");
	_strcat(error, shell_data->args[0]);
	_strcat(error, ": Illegal number: ");
	_strcat(error, shell_data->args[1]);
	_strcat(error, "\n\0");
	free(line_number);

	return (error);
}
