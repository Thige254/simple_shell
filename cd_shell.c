#include "shell.h"

/**
 * change_directory_shell - changes current directory
 *
 * @datash: Data relevant
 * Return: 1 on success
 */
int change_directory_shell(data_shell *datash)
{
	char *dir;
	int is_home, is_home2, is_double_dash;

	dir = datash->args[1];

	if (dir != NULL)
	{
		is_home = _str_compare("$HOME", dir);
		is_home2 = _str_compare("~", dir);
		is_double_dash = _str_compare("--", dir);
	}

	if (dir == NULL || !is_home || !is_home2 || !is_double_dash)
	{
		change_directory_to_home(datash);
		return (1);
	}

	if (_str_compare("-", dir) == 0)
	{
		change_directory_to_previous(datash);
		return (1);
	}

	if (_str_compare(".", dir) == 0 || _str_compare("..", dir) == 0)
	{
		change_directory_dot(datash);
		return (1);
	}

	change_directory_to(datash);

	return (1);
}
