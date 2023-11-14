#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>

/**
 * struct shell_data - Structure to hold data relevant to the shell.
 * @arguments: Array of command arguments.
 * @environment: Array of environment variables.
 * @status: Exit status of the last command.
 * @counter: Counter for line numbers (used in error messages).
 */
typedef struct shell_data
{
	char **arguments;	/**< Array of command arguments */
	char **environment; /**< Array of environment variables */
	int status;			/**< Exit status of the last command */
	int counter;		/**< Counter for line numbers (used in error messages) */
} shell_data;

/* Function prototypes */

/* From exec_line.c */
int execute_line(shell_data *shell_data);

/* ... (other existing function prototypes) */

/* New function prototypes */
int change_directory_shell(shell_data *datash);
char *generate_cd_error_message(shell_data *shell_data);
char *generate_not_found_error_message(shell_data *shell_data);
char *generate_exit_shell_error_message(shell_data *shell_data);

/* Utility functions */
char *_str_copy(char *dest, const char *src);
char *_str_cat(char *dest, const char *src);
char *convert_to_string(int num);
int _str_length(const char *str);
int _str_compare(const char *str1, const char *str2);

/* Directory-related functions */
void change_directory_to_home(shell_data *datash);
void change_directory_to_previous(shell_data *datash);
void change_directory_dot(shell_data *datash);
void change_directory_to(shell_data *datash);

#endif /* SHELL_H */
