#include "shell.h"

/**
 * display_help - Help information for the builtin help.
 * Return: no return
 */
void display_help(void)
{
	char *help = "help: help [-dms] [pattern ...]\n";

	write(STDOUT_FILENO, help, _custom_strlen(help));
	help = "\tDisplay information about builtin commands.\n ";
	write(STDOUT_FILENO, help, _custom_strlen(help));
	help = "Displays brief summaries of builtin commands.\n";
	write(STDOUT_FILENO, help, _custom_strlen(help));
}

/**
 * display_alias_help - Help information for the builtin alias.
 * Return: no return
 */
void display_alias_help(void)
{
	char *help = "alias: alias [-p] [name[=value]...]\n";

	write(STDOUT_FILENO, help, _custom_strlen(help));
	help = "\tDefine or display aliases.\n ";
	write(STDOUT_FILENO, help, _custom_strlen(help));
}

/**
 * display_cd_help - Help information for the builtin alias.
 * Return: no return
 */
void display_cd_help(void)
{
	char *help = "cd: cd [-L|[-P [-e]] [-@]] [dir]\n";

	write(STDOUT_FILENO, help, _custom_strlen(help));
	help = "\tChange the shell working directory.\n ";
	write(STDOUT_FILENO, help, _custom_strlen(help));
}
