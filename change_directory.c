#include <stdlib.h>
#include <unistd.h>
#include "shell.h"

/**
 * set_directory_variables - sets environment variables for directory changes
 *
 * @datash: data relevant (environ)
 * @old_path: old path value
 * @new_path: new path value
 * @status: status to set
 */
void set_directory_variables(data_shell *datash, char *old_path, char *new_path, int status)
{
	set_env("OLDPWD", old_path, datash);
	chdir(new_path);
	set_env("PWD", new_path, datash);
	datash->status = status;
}

/**
 * update_path_and_status - updates path and status based on conditions
 *
 * @datash: data relevant (environ)
 * @copy_current_path: copied current path
 * @copy_tokenized_path: tokenized path
 */
static void update_path_and_status(data_shell *datash,
								   char *copy_current_path, char *copy_tokenized_path)
{
	if (copy_tokenized_path != NULL)
	{
		reverse_string(copy_tokenized_path);
		set_directory_variables(datash, copy_current_path, copy_tokenized_path, 0);
	}
	else
	{
		set_directory_variables(datash, copy_current_path, "/", 0);
	}
}

/**
 * change_directory_parent - changes to the parent directory
 *
 * @datash: data relevant (environ)
 */
void change_directory_parent(data_shell *datash)
{
	char current_path[PATH_MAX];
	char *user_dir, *copy_current_path, *copy_tokenized_path;

	getcwd(current_path, sizeof(current_path));
	copy_current_path = _strdup(current_path);

	user_dir = datash->args[1];
	if (_strcmp(".", user_dir) == 0)
	{
		set_directory_variables(datash, copy_current_path, copy_current_path, 0);
		free(copy_current_path);
		return;
	}

	if (_strcmp("/", copy_current_path) == 0)
	{
		free(copy_current_path);
		return;
	}

	copy_tokenized_path = copy_current_path;
	copy_tokenized_path = _strtok(copy_tokenized_path, "/");
	update_path_and_status(datash, copy_current_path, copy_tokenized_path);

	free(copy_current_path);
}

/**
 * change_directory_to - changes to a directory given
 * by the user
 *
 * @datash: data relevant (directories)
 */
void change_directory_to(data_shell *datash)
{
	char current_path[PATH_MAX];
	char *user_dir, *copy_current_path, *copy_user_dir;

	getcwd(current_path, sizeof(current_path));

	user_dir = datash->args[1];
	if (chdir(user_dir) == -1)
	{
		get_error(datash, 2);
		return;
	}

	copy_current_path = _strdup(current_path);
	set_env("OLDPWD", copy_current_path, datash);

	copy_user_dir = _strdup(user_dir);
	set_env("PWD", copy_user_dir, datash);

	free(copy_current_path);
	free(copy_user_dir);

	datash->status = 0;

	chdir(user_dir);
}
