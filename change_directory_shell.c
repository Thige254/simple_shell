#include "shell.h"

/**
 * change_directory_shell - changes current directory
 *
 * @datash: data relevant
 * Return: 1 on success
 */
int change_directory_shell(data_shell *datash)
{
	char *user_dir;
	int is_home, is_home2, is_double_dash;

	user_dir = datash->args[1];

	if (user_dir != NULL)
	{
		is_home = _strcmp("$HOME", user_dir);
		is_home2 = _strcmp("~", user_dir);
		is_double_dash = _strcmp("--", user_dir);
	}

	if (user_dir == NULL || !is_home || !is_home2 || !is_double_dash)
	{
		change_directory_to_home(datash);
		return (1);
	}

	if (_strcmp("-", user_dir) == 0)
	{
		change_directory_previous(datash);
		return (1);
	}

	if (_strcmp(".", user_dir) == 0 || _strcmp("..", user_dir) == 0)
	{
		change_directory_parent(datash);
		return (1);
	}

	change_directory_to(datash);

	return (1);
}
