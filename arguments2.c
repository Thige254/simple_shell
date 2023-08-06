#include "shell.h"

int can_not_open_file(char *file_path);
int process_file_commands(char *file_path, int *exe_ret);

/**
 * can_not_open_file - If the file doesn't exist or lacks proper permissions, print
 * a can't open error.
 * @file_path: Path to the supposed file.
 *
 * Return: 127.
 */
int can_not_open_file(char *file_path)
{
	char *error, *hist_str;
	int len;

	hist_str = int_to_str(hist);
	if (!hist_str)
		return (127);

	len = str_len(name) + str_len(hist_str) + str_len(file_path) + 16;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		free(hist_str);
		return (127);
	}

	str_cpy(error, name);
	str_cat(error, ": ");
	str_cat(error, hist_str);
	str_cat(error, ": Can't open ");
	str_cat(error, file_path);
	str_cat(error, "\n");

	free(hist_str);
	write(STDERR_FILENO, error, len);
	free(error);
	return (127);
}

/**
 * process_file_commands - Takes a file and attempts to run the commands stored
 * within.
 * @file_path: Path to the file.
 * @exe_ret: Return value of the last executed command.
 *
 * Return: If file couldn't be opened - 127.
 *         If malloc fails - -1.
 *         Otherwise the return value of the last command ran.
 */
int process_file_commands(char *file_path, int *exe_ret)
{
	FILE *file;
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	int ret = 0;

	hist = 0;
	file = fopen(file_path, "r");
	if (file == NULL)
	{
		*exe_ret = can_not_open_file(file_path);
		return (*exe_ret);
	}

	while ((read = getline(&line, &len, file)) != -1) 
	{
		variable_replacement(&line, exe_ret);
		handle_line(&line, len);
		ret = process_args(line, exe_ret);
	}

	fclose(file);
	if (line)
		free(line);

	return (ret);
}
