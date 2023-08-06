#include "shell.h"

char *fill_path_dir(char *path);
list_t *get_path_dir(char *path);

/**
 * get_location - Locates a command in the PATH.
 * @command: The command to locate.
 *
 * Return: If an error occurs or the command cannot be located - NULL.
 *         Otherwise - the full pathname of the command.
 */
char *get_location(char *command)
{
	list_t *dirs, *head;
	struct stat st;
	char *dir_path;

	dirs = get_path_dir(getenv("PATH"));
	head = dirs;

	while (dirs)
	{
		dir_path = path_join(dirs->dir, command);

		if (stat(dir_path, &st) == 0)
		{
			free_list(head);
			return (dir_path);
		}

		dirs = dirs->next;
		free(dir_path);
	}

	free_list(head);

	return (NULL);
}

/**
 * fill_path_dir - Replaces leading/sandwiched/trailing
 *                 colons (:) with current working directory in a path.
 * @path: The colon-separated list of directories.
 *
 * Return: A copy of path with any leading/sandwiched/trailing colons replaced
 *         with the current working directory.
 */
char *fill_path_dir(char *path)
{
	char *path_copy;
	char *pwd = getenv("PWD");

	path_copy = replace_string(path, "::", pwd);
	path_copy = replace_string(path_copy, ":", pwd);

	return (path_copy);
}

/**
 * get_path_dir - Tokenizes a colon-separated list of
 *                directories into a list_s linked list.
 * @path: The colon-separated list of directories.
 *
 * Return: A pointer to the initialized linked list.
 */
list_t *get_path_dir(char *path)
{
	char **dirs;
	list_t *head = NULL;

	path = fill_path_dir(path);
	dirs = split_string(path, ":");

	for (int index = 0; dirs[index]; index++)
	{
		if (add_node_end(&head, dirs[index]) == NULL)
		{
			free_list(head);
			free(dirs);
			return (NULL);
		}
	}

	free(dirs);

	return (head);
}
