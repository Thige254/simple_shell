#include "shell.h"

void sig_handler(int sig);
int execute(char **args, char **front);

void sig_handler(int sig)
{
	(void)sig;
	signal(SIGINT, sig_handler);
	write(STDIN_FILENO, "\n$ ", 3);
}

int execute(char **args, char **front)
{
	pid_t child_pid;
	int status, ret = 0;
	char *command = args[0];
	int flag = command[0] != '/' && command[0] != '.';

	if (flag)
		command = get_location(command);

	if (!command || (access(command, F_OK) == -1))
		ret = errno == EACCES ? create_error(args, 126) : create_error(args, 127);
	else
	{
		child_pid = fork();
		if (child_pid == -1)
		{
			if (flag)
				free(command);
			perror("Error child:");
			return (1);
		}

		if (child_pid == 0)
		{
			execve(command, args, environ);
			if (errno == EACCES)
				ret = create_error(args, 126);
			free_env();
			free_args(args, front);
			free_alias_list(aliases);
			_exit(ret);
		}
		else
		{
			wait(&status);
			ret = WEXITSTATUS(status);
		}
	}

	if (flag)
		free(command);

	return (ret);
}

int main(int argc, char *argv[])
{
	int ret = 0, retn;
	int *exe_ret = &retn;

	name = argv[0];
	hist = 1;
	aliases = NULL;
	signal(SIGINT, sig_handler);

	*exe_ret = 0;
	environ = _copyenv();
	if (!environ)
		exit(-100);

	if (argc != 1)
	{
		ret = proc_file_commands(argv[1], exe_ret);
		free_env();
		free_alias_list(aliases);
		return (*exe_ret);
	}

	if (!isatty(STDIN_FILENO))
	{
		while (ret != END_OF_FILE && ret != EXIT)
			ret = handle_args(exe_ret);
		free_env();
		free_alias_list(aliases);
		return (*exe_ret);
	}

	while (1)
	{
		write(STDOUT_FILENO, "$ ", 2);
		ret = handle_args(exe_ret);
		if (ret == END_OF_FILE || ret == EXIT)
		{
			if (ret == END_OF_FILE)
				write(STDOUT_FILENO, "\n", 1);
			free_env();
			free_alias_list(aliases);
			exit(*exe_ret);
		}
	}

	free_env();
	free_alias_list(aliases);
	return (*exe_ret);
}
