#include "shell.h"

/**
 * execute_line - finds built-ins and commands
 *
 * @shell_data: data relevant to the shell (arguments)
 * Return: 1 on success.
 */
int execute_line(shell_data *shell_data)
{
	int (*builtin_func)(shell_data *shell_data);

	if (shell_data->arguments[0] == NULL)
		return (1);

	builtin_func = get_builtin(shell_data->arguments[0]);

	if (builtin_func != NULL)
		return (builtin_func(shell_data));

	return (execute_command(shell_data));
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
