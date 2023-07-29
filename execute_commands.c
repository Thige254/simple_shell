#include "shell.h"

/**
 * execute_command - executes a given command
 * @command: command to be executed
 * Description: This function takes a command, forks a new process and then
 * executes the command in the child process.
 * If the command cannot be executed,
 * it prints an error message and the child process is terminated.
 */
void execute_command(char *command)
{
	pid_t pid;
	int status;
	char *argv[2];

	/* Fork child process */
	pid = fork();
	if (pid == 0)
	{
		/*child process */
		argv[0] = command;
		argv[1] = NULL;

		/* Execute the command */
		if (execve(command, argv, NULL) == -1)
		{
			/*terminate child process on failure*/
			perror("Error executing command");
			exit(EXIT_FAILURE);
		}
	} else if (pid < 0)
	{
		/* If forking failed, print error message */
		perror("Error forking");
	} else
	{
		/* Parent proccess */
		do {
			waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
}
