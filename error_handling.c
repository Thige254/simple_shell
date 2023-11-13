#include "shell.h"
#include "string_conversions.c"

/**
 * concat_error_message - Concatenates error message for error handling
 *
 * @shell_data: Shell data structure
 * @msg: Message to print
 * @error_msg: Output error message
 * @line_str: Counter lines
 * Return: Error message
 */
char *concat_error_message(data_shell *shell_data,
char *msg, char *error_msg, char *line_str)
{
	char *illegal_flag;

	_custom_strcpy(error_msg, shell_data->av[0]);
	_custom_strcat(error_msg, ": ");
	_custom_strcat(error_msg, line_str);
	_custom_strcat(error_msg, ": ");
	_custom_strcat(error_msg, shell_data->args[0]);
	_custom_strcat(error_msg, msg);

	if (shell_data->args[1][0] == '-')
	{
		illegal_flag = malloc(3);
		illegal_flag[0] = '-';
		illegal_flag[1] = shell_data->args[1][1];
		illegal_flag[2] = '\0';
		_custom_strcat(error_msg, illegal_flag);
		free(illegal_flag);
	}
	else
	{
		_custom_strcat(error_msg, shell_data->args[1]);
	}

	_custom_strcat(error_msg, "\n");
	_custom_strcat(error_msg, "\0");
	return (error_msg);
}

/**
 * error_cd - Error message for cd command
 * @shell_data: Shell data structure
 * Return: Error message
 */
char *error_cd(data_shell *shell_data)
{
	int length, len_id;
	char *error, *line_str, *msg;

	line_str = _custom_itoa(shell_data->counter);
	if (shell_data->args[1][0] == '-')
	{
		msg = ": Illegal option ";
		len_id = 2;
	}
	else
	{
		msg = ": can't cd to ";
		len_id = _custom_strlen(shell_data->args[1]);
	}

	length = _custom_strlen(shell_data->av[0])
	+ _custom_strlen(shell_data->args[0]);
	length += _custom_strlen(line_str)
	+ _custom_strlen(msg) + len_id + 5;
	error = malloc(sizeof(char) * (length + 1));

	if (error == 0)
	{
		free(line_str);
		return (NULL);
	}

	error = concat_error_message(shell_data, msg, error, line_str);

	free(line_str);

	return (error);
}

/**
 * error_command_not_found - Generic error message for command not found
 * @shell_data: Shell data structure
 * Return: Error message
 */
char *error_command_not_found(data_shell *shell_data)
{
	int length;
	char *error;
	char *line_str;

	line_str = _custom_itoa(shell_data->counter);
	length = _custom_strlen(shell_data->av[0])
	+ _custom_strlen(line_str);
	length += _custom_strlen(shell_data->args[0]) + 16;
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
	_custom_strcat(error, ": not found\n");
	_custom_strcat(error, "\0");
	free(line_str);
	return (error);
}

/**
 * error_exit_shell - Generic error message for exit command
 * @shell_data: Shell data structure
 *
 * Return: Error message
 */
char *error_exit_shell(data_shell *shell_data)
{
	int length;
	char *error;
	char *line_str;

	line_str = _custom_itoa(shell_data->counter);
	length = _custom_strlen(shell_data->av[0]) + _custom_strlen(line_str);
	length += _custom_strlen(shell_data->args[0])
	+ _custom_strlen(shell_data->args[1]) + 23;
	error = malloc(sizeof(char) * (length + 1));
	if (error == 0)
	{
		free(line_str);
		return (NULL);
	}
	_custom_strcpy(error, shell_data->av[0]);
	_custom_strcat(error, ": ");
	_custom_strcat(error, line_str);
	_custom_strcat(error, ": ");
	_custom_strcat(error, shell_data->args[0]);
	_custom_strcat(error, ": Illegal number: ");
	_custom_strcat(error, shell_data->args[1]);
	_custom_strcat(error, "\n\0");
	free(line_str);

	return (error);
}
