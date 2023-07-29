#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include "shell.h"

/**
 * main - Main entry point for the shell.
 * Return: 0 (EXIT_SUCCESS)
 */

int main(void)
{
	shell_loop();
	return (EXIT_SUCCESS);
}
