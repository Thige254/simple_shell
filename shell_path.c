#include "shell.h"

/**
 * get_command_path - Checks if command is a full path or needs to be located.
 * @args: The argument array with the command at index 0.
 * @flag: Flag that determines if command is a full path or not.
 *
 * Return: Full command path if command is not a full path, otherwise, args[0].
 */
char *get_command_path(char **args, int *flag)
{
	char *command = args[0];

	if (command[0] != '/' && command[0] != '.')
	{
		*flag = 1;
		command = get_location(command);
	}
	return (command);
}

/**
 * execute_command - Executes a command in a child process.
 * @args: Argument array.
 * @front: A pointer to the beginning of args.
 * @command: The command to execute.
 * @exe_ret: Return value of the last executed command.
 * @flag: Flag that determines if command is a full path or not.
 *
 * Return: void
 */
void execute_command(char **args, char **front, char *command,
		int *exe_ret, int flag)
{
	pid_t child_pid;
	int status;
	char **env = _getenv("PATH");

	if (!command || access(command, F_OK) == -1)
	{
		if (errno == EACCES)
			*exe_ret = (create_error(args, 126));
		else
			*exe_ret = (create_error(args, 127));
	}
	else
	{
		child_pid = fork();
		if (child_pid == -1)
		{
			if (flag)
				free(command);
			perror("Error child:");
			return;
		}
		if (child_pid == 0)
		{
			execve(command, args, env);
			if (errno == EACCES)
				*exe_ret = (create_error(args, 126));
			free_env();
			free_args(args, front);
			free_alias_list(aliases);
			_exit(*exe_ret);
		}
		else
		{
			wait(&status);
			*exe_ret = WEXITSTATUS(status);
		}
	}
	if (flag)
		free(command);
}

/**
 * execute - Executes a command.
 * @args: Argument array.
 * @front: A pointer to the beginning of args.
 *
 * Return: If an error occurs - a corresponding error code.
 *         O/w - The exit value of the last executed command.
 */
int execute(char **args, char **front)
{
	int flag = 0;
	int exe_ret = 0;

	char *command = get_command_path(args, &flag);
	execute_command(args, front, command, &exe_ret, flag);

	return (exe_ret);
}
