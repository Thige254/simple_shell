#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include "shell2.h"

/**
 * main - Main entry point for the shell.
 * Return: (EXIT_SUCCESS) or exit status
 */

int main(void)
{
	shell_loop();
	return (0);
}
