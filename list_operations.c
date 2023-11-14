#include "shell.h"

/**
 * compare_separator_name - compares separator names
 * with the name passed.
 * @separator: name of the separator
 * @name: name passed
 *
 * Return: 0 if they are not equal. Another value if they are.
 */
int compare_separator_name(const char *separator, const char *name)
{
	int i;

	for (i = 0; separator[i] != '='; i++)
	{
		if (separator[i] != name[i])
		{
			return (0);
		}
	}

	return (i + 1);
}

/**
 * get_separator_value - get a separator value
 * @name: name of the separator
 * @separators: separator array
 *
 * Return: value of the separator if found.
 * Otherwise, returns NULL.
 */
char *get_separator_value(const char *name, char **separators)
{
	char *ptr_separator;
	int i, move;

	/* Initialize ptr_separator value */
	ptr_separator = NULL;
	move = 0;
	/* Compare all separators */
	/* separators is declared in the header file */
	for (i = 0; separators[i]; i++)
	{
		/* If name and separator are equal */
		move = compare_separator_name(separators[i], name);
		if (move)
		{
			ptr_separator = separators[i];
			break;
		}
	}

	return (ptr_separator + move);
}

/**
 * print_separators - prints the separator array
 *
 * @shell_data: data relevant.
 * Return: 1 on success.
 */
int print_separators(shell_data *shell_data)
{
	int i, j;

	for (i = 0; shell_data->separators[i]; i++)
	{

		for (j = 0; shell_data->separators[i][j]; j++)
			;

		write(STDOUT_FILENO, shell_data->separators[i], j);
		write(STDOUT_FILENO, "\n", 1);
	}
	shell_data->status = 0;

	return (1);
}
