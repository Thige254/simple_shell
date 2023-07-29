#include "shell.h"
/**
 * shell_loop - main loop. Its where commands are read and executed.
 */

void shell_loop(void)
{
	char *line;
	char *command;

	while (1)
	{
		printf("> ");
		line = read_command();
		command = strtok(line, "\n");
		if (strcmp(command, "exit") == 0)
		{
			free(line);
			exit(EXIT_SUCCESS);
		}
		execute_command(command);
		free(line);
	}
}
