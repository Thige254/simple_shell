#include "shell.h"

/**
 * is_colon - checks if ':' is in the current directory.
 * @path: type char pointer char.
 * @i: type int pointer of index.
 * Return: 1 if the path is searchable in the cd, 0 otherwise.
 */
int is_colon(char *path, int *i)
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
 * find_command - locates a command
 *
 * @command: command name
 * @environment: environment variable
 * Return: location of the command.
 */
char *find_command(char *command, char **environment)
{
	char *path, *path_ptr, *token_path, *directory;
	int len_directory, len_command, i;
	struct stat st;

	path = _getenv("PATH", environment);
	if (path)
	{
		path_ptr = _strdup(path);
		len_command = _strlen(command);
		token_path = _strtok(path_ptr, ":");
		i = 0;
		while (token_path != NULL)
		{
			if (is_colon(path, &i))
				if (stat(command, &st) == 0)
					return (command);
			len_directory = _strlen(token_path);
			directory = malloc(len_directory + len_command + 2);
			_strcpy(directory, token_path);
			_strcat(directory, "/");
			_strcat(directory, command);
			_strcat(directory, "\0");
			if (stat(directory, &st) == 0)
			{
				free(path_ptr);
				return (directory);
			}
			free(directory);
			token_path = _strtok(NULL, ":");
		}
		free(path_ptr);
		if (stat(command, &st) == 0)
			return (command);
		return (NULL);
	}
	if (command[0] == '/')
		if (stat(command, &st) == 0)
			return (command);
	return (NULL);
}

/**
 * is_executable - determines if it's an executable
 *
 * @shell_data: data structure
 * Return: 0 if it's not an executable, other number if it is
 */
int is_executable(shell_data *shell_data)
{
	struct stat st;
	int i;
	char *input;

	input = shell_data->arguments[0];
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
	get_error(shell_data, 127);
	return (-1);
}

/**
 * check_command_error - verifies if the user has permissions to access
 *
 * @directory: destination directory
 * @shell_data: data structure
 * Return: 1 if there is an error, 0 if not
 */
int check_command_error(char *directory, shell_data *shell_data)
{
	if (directory == NULL)
	{
		get_error(shell_data, 127);
		return (1);
	}

	if (_strcmp(shell_data->arguments[0], directory) != 0)
	{
		if (access(directory, X_OK) == -1)
		{
			get_error(shell_data, 126);
			free(directory);
			return (1);
		}
		free(directory);
	}
	else
	{
		if (access(shell_data->arguments[0], X_OK) == -1)
		{
			get_error(shell_data, 126);
			return (1);
		}
	}
	return (0);
}
/**
 * execute_command - executes command lines
 *
 * @shell_data: data relevant (arguments and input)
 * Return: 1 on success.
 */
int execute_command(shell_data *shell_data)
{
	pid_t pid;
	pid_t wait_pid;
	int state;
	int exec;
	char *directory;
	(void) wait_pid;
	exec = is_executable(shell_data);
	if (exec == -1)
		return (1);
	if (exec == 0)
	{
		directory = find_command(shell_data->arguments[0], shell_data->environment);
		if (check_command_error(directory, shell_data) == 1)
			return (1);
	}
	pid = fork();
	if (pid == 0)
	{
		if (exec == 0)
			directory = find_command(shell_data->arguments[0],
			shell_data->environment);
		else
			directory = shell_data->arguments[0];
		execve(directory + exec, shell_data->arguments, shell_data->environment);
	}
	else if (pid < 0)
	{
		perror(shell_data->arguments[0]);
		return (1);
	}
	else
	{
		do {
			wait_pid = waitpid(pid, &state, WUNTRACED);
		} while (!WIFEXITED(state) && !WIFSIGNALED(state));
	}
	shell_data->status = state / 256;
	return (1);
}
