#include "shell.h"

/**
 * build_cd_error_message - function
 * that builds the error message for cd command
 *
 * @shell_data: Data relevant (directory)
 * @msg: Message to print
 * @error: Output message
 * @line_number: Counter lines
 * Return: Error message
 */
char *build_cd_error_message(shell_data *shell_data,
							 char *msg, char *error, char *line_number)
{
	char *illegal_flag;

	_str_copy(error, shell_data->arguments[0]);
	_str_cat(error, ": ");
	_str_cat(error, line_number);
	_str_cat(error, ": ");
	_str_cat(error, shell_data->arguments[0]);
	_str_cat(error, msg);
	if (shell_data->arguments[1][0] == '-')
	{
		illegal_flag = malloc(3);
		illegal_flag[0] = '-';
		illegal_flag[1] = shell_data->arguments[1][1];
		illegal_flag[2] = '\0';
		_str_cat(error, illegal_flag);
		free(illegal_flag);
	}
	else
	{
		_str_cat(error, shell_data->arguments[1]);
	}

	_str_cat(error, "\n");
	_str_cat(error, "\0");
	return (error);
}

/**
 * generate_cd_error_message - error message for cd command in get_cd
 * @shell_data: Data relevant (directory)
 * Return: Error message
 */
char *generate_cd_error_message(shell_data *shell_data)
{
	int length, len_id;
	char *error, *line_number, *msg;

	line_number = convert_to_string(shell_data->counter);
	if (shell_data->arguments[1][0] == '-')
	{
		msg = ": Illegal option ";
		len_id = 2;
	}
	else
	{
		msg = ": can't cd to ";
		len_id = _str_length(shell_data->arguments[1]);
	}

	length = _str_length(shell_data->arguments[0])
	+ _str_length(shell_data->arguments[0]);
	length += _str_length(line_number) + _str_length(msg) + len_id + 5;
	error = malloc(sizeof(char) * (length + 1));

	if (error == NULL)
	{
		free(line_number);
		return (NULL);
	}

	error = build_cd_error_message(shell_data, msg, error, line_number);

	free(line_number);

	return (error);
}

/**
 * generate_not_found_error_message - generic error
 * message for command not found
 * @shell_data: Data relevant (counter, arguments)
 * Return: Error message
 */
char *generate_not_found_error_message(shell_data *shell_data)
{
	int length;
	char *error;
	char *line_number;

	line_number = convert_to_string(shell_data->counter);
	length = _str_length(shell_data->arguments[0])
	+ _str_length(line_number);
	length += _str_length(shell_data->arguments[0]) + 16;
	error = malloc(sizeof(char) * (length + 1));
	if (error == NULL)
	{
		free(line_number);
		return (NULL);
	}
	_str_copy(error, shell_data->arguments[0]);
	_str_cat(error, ": ");
	_str_cat(error, line_number);
	_str_cat(error, ": ");
	_str_cat(error, shell_data->arguments[0]);
	_str_cat(error, ": not found\n");
	_str_cat(error, "\0");
	free(line_number);
	return (error);
}

/**
 * generate_exit_shell_error_message - generic error
 * message for exit in get_exit
 * @shell_data: Data relevant (counter, arguments)
 * Return: Error message
 */
char *generate_exit_shell_error_message(shell_data *shell_data)
{
	int length;
	char *error;
	char *line_number;

	line_number = convert_to_string(shell_data->counter);
	length = _str_length(shell_data->arguments[0]) + _str_length(line_number);
	length += _str_length(shell_data->arguments[0]) +
			  _str_length(shell_data->arguments[1]) + 23;
	error = malloc(sizeof(char) * (length + 1));
	if (error == NULL)
	{
		free(line_number);
		return (NULL);
	}
	_str_copy(error, shell_data->arguments[0]);
	_str_cat(error, ": ");
	_str_cat(error, line_number);
	_str_cat(error, ": ");
	_str_cat(error, shell_data->arguments[0]);
	_str_cat(error, ": Illegal number: ");
	_str_cat(error, shell_data->arguments[1]);
	_str_cat(error, "\n\0");
	free(line_number);

	return (error);
}
