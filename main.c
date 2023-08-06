#include "shell.h"

void sig_handler(int sig);
int process_args(char **args, char **front);

/**
 * sig_handler - Prints a new prompt when instructed
 * @sig: The signal received.
 */
void sig_handler(int sig)
{
	(void)sig;
	signal(SIGINT, sig_handler);
	write(STDIN_FILENO, "\n$ ", 3);
}

/**
 * main - Runs a simple-shell command interpreter.
 * @argc: The number of arguments supplied to the program.
 * @argv: An array of pointers to the arguments.
 *
 * Return: The return value of the last executed command.
 */
int main(int argc, char *argv[])
{
	int ret = 0;
	int exe_ret = 0;
	char *prompt = "$ ";
	char *new_line = "\n";
	char **args;

	name = argv[0];
	hist = 1;
	aliases = NULL;
	signal(SIGINT, sig_handler);

	environ = _copyenv();
	if (!environ)
		exit(-100);

	if (argc != 1)
	{
		ret = process_file_commands(argv[1], &exe_ret);
		free_env();
		free_alias_list(aliases);
		return (exe_ret);
	}

	if (!isatty(STDIN_FILENO))
	{
		while ((args = get_command()) != NULL)
		{
			ret = process_args(args, &exe_ret);
			if (ret == END_OF_FILE || ret == EXIT)
			{
				if (ret == END_OF_FILE)
					write(STDOUT_FILENO, new_line, 1);
				free_env();
				free_alias_list(aliases);
				exit(exe_ret);
			}
		}
	}

	while (1)
	{
		write(STDOUT_FILENO, prompt, 2);
		args = get_command();
		ret = process_args(args, &exe_ret);
		if (ret == END_OF_FILE || ret == EXIT)
		{
			if (ret == END_OF_FILE)
				write(STDOUT_FILENO, new_line, 1);
			free_env();
			free_alias_list(aliases);
			exit(exe_ret);
		}
	}

	free_env();
	free_alias_list(aliases);
	return (exe_ret);
}
