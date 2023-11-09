#include "shell.h"

/**
 * display_prompt - Display the shell prompt and get user input.
 * Return: the user input as a string.
 */
char *display_prompt(void)
{
	char *input = NULL;
	size_t len = 0;

	while (1)
	{
		puts("$ "); /*Replaced _puts with puts*/
		if (getline(&input, &len, stdin) == -1)
		{
			if (isatty(STDIN_FILENO))
			{
				putchar('\n'); /*Replaced _putchar with putchar */
				free(input);
				input = NULL;
			}
			else
			{
				free(input);
				exit(EXIT_SUCCESS);
			}
		}
		if (input && *input)
		{
			break;
		}
	}

	return (input);
}
