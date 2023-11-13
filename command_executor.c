#include "shell.h"

/**
 * is_current_directory - checks if ":" is in the current directory.
 * @path: type char pointer.
 * @i: type int pointer of index.
 * Return: 1 if the path is searchable in the current directory, 0 otherwise.
 */
int is_current_directory(char *path, int *i)
{
	if (path[*i] == ':')
		return (1);

	while (path[*i] != ':' && path[*i])
	{
		*i += 1;
	}

	if (path[*i])
		*i += 1;

	return (0);
}

/**
 * find_command_location - locates a command
 *
 * @cmd: command name
 * @_environ: environment variable
 * Return: location of the command.
 */
char *find_command_location(char *cmd, char **_environ)
{
	char *path, *ptr_path, *token_path, *dir;
	int len_dir, len_cmd, i;
	struct stat st;

	path = _getenv("PATH", _environ);
	if (path)
	{
		ptr_path = _strdup(path);
		len_cmd = _strlen(cmd);
		token_path = _strtok(ptr_path, ":");
		i = 0;
		while (token_path != NULL)
		{
			if (is_current_directory(path, &i))
				if (stat(cmd, &st) == 0)
					return (cmd);
			len_dir = _strlen(token_path);
			dir = malloc(len_dir + len_cmd + 2);
			_strcpy(dir, token_path);
			_strcat(dir, "/");
			_strcat(dir, cmd);
			_strcat(dir, "\0");
			if (stat(dir, &st) == 0)
			{
				free(ptr_path);
				return (dir);
			}
			free(dir);
			token_path = _strtok(NULL, ":");
		}
		free(ptr_path);
		if (stat(cmd, &st) == 0)
			return (cmd);
		return (NULL);
	}
	if (cmd[0] == '/')
		if (stat(cmd, &st) == 0)
			return (cmd);
	return (NULL);
}

/**
 * determine_executable - determines if a command is an executable
 *
 * @datash: data structure
 * Return: 0 if it is not an executable, other number if it is
 */
int determine_executable(data_shell *datash)
{
	struct stat st;
	int i;
	char *input;

	input = datash->args[0];
	for (i = 0; input[i]; i++)
	{
		if (input[i] == '.')
		{
			if (input[i + 1] == '.')
				return (0);
			if (input[i + 1] == '/')
				continue;
			else
				break;
		}
		else if (input[i] == '/' && i != 0)
		{
			if (input[i + 1] == '.')
				continue;
			i++;
			break;
		}
		else
			break;
	}
	if (i == 0)
		return (0);

	if (stat(input + i, &st) == 0)
	{
		return (i);
	}
	get_error(datash, 127);
	return (-1);
}

/**
 * verify_command_error - verifies if the user has permissions to access
 *
 * @dir: destination directory
 * @datash: data structure
 * Return: 1 if there is an error, 0 if not
 */
int verify_command_error(char *dir, data_shell *datash)
{
	if (dir == NULL)
	{
		get_error(datash, 127);
		return (1);
	}

	if (_strcmp(datash->args[0], dir) != 0)
	{
		if (access(dir, X_OK) == -1)
		{
			get_error(datash, 126);
			free(dir);
			return (1);
		}
		free(dir);
	}
	else
	{
		if (access(datash->args[0], X_OK) == -1)
		{
			get_error(datash, 126);
			return (1);
		}
	}

	return (0);
}

/**
 * execute_command - executes command lines
 *
 * @datash: data relevant (args and input)
 * Return: 1 on success.
 */
int execute_command(data_shell *datash)
{
	pid_t pid;
	pid_t wait_pid;
	int state;
	int exec;
	char *dir;
	(void)wait_pid;

	exec = determine_executable(datash);
	if (exec == -1)
		return (1);
	if (exec == 0)
	{
		dir = find_command_location(datash->args[0], datash->_environ);
		if (verify_command_error(dir, datash) == 1)
			return (1);
	}

	pid = fork();
	if (pid == 0)
	{
		if (exec == 0)
			dir = find_command_location(datash->args[0], datash->_environ);
		else
			dir = datash->args[0];
		execve(dir + exec, datash->args, datash->_environ);
	}
	else if (pid < 0)
	{
		perror(datash->av[0]);
		return (1);
	}
	else
	{
		do {
			wait_pid = waitpid(pid, &state, WUNTRACED);
		} while (!WIFEXITED(state) && !WIFSIGNALED(state));
	}
	datash->status = state / 256;
	return (1);
}
