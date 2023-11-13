#include "shell.h"

/**
 * change_directory_previous - changes to the previous directory
 *
 * @datash: data relevant (environ)
 * Return: no return
 */
void change_directory_previous(data_shell *datash)
{
	char current_path[PATH_MAX];
	char *previous_pwd, *old_pwd, *copy_current_path, *copy_old_pwd;

	getcwd(current_path, sizeof(current_path));
	copy_current_path = _strdup(current_path);

	previous_pwd = _getenv("OLDPWD", datash->_environ);

	if (previous_pwd == NULL)
		copy_old_pwd = copy_current_path;
	else
		copy_old_pwd = _strdup(previous_pwd);

	set_env("OLDPWD", copy_current_path, datash);

	if (chdir(copy_old_pwd) == -1)
		set_env("PWD", copy_current_path, datash);
	else
		set_env("PWD", copy_old_pwd, datash);

	old_pwd = _getenv("PWD", datash->_environ);

	write(STDOUT_FILENO, old_pwd, _strlen(old_pwd));
	write(STDOUT_FILENO, "\n", 1);

	free(copy_current_path);
	if (previous_pwd)
		free(copy_old_pwd);

	datash->status = 0;

	chdir(old_pwd);
}

/**
 * change_directory_to_home - changes to home directory
 *
 * @datash: data relevant (environ)
 * Return: no return
 */
void change_directory_to_home(data_shell *datash)
{
	char *current_pwd, *home;
	char current_path[PATH_MAX];

	getcwd(current_path, sizeof(current_path));
	current_pwd = _strdup(current_path);

	home = _getenv("HOME", datash->_environ);

	if (home == NULL)
	{
		set_env("OLDPWD", current_pwd, datash);
		free(current_pwd);
		return;
	}

	if (chdir(home) == -1)
	{
		get_error(datash, 2);
		free(current_pwd);
		return;
	}

	set_env("OLDPWD", current_pwd, datash);
	set_env("PWD", home, datash);
	free(current_pwd);
	datash->status = 0;
}
