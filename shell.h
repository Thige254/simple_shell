#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>

/* Structure to hold data relevant to the shell */
typedef struct shell_data
{
	char **arguments;	/* Array of command arguments */
	char **environment; /* Array of environment variables */
	int status;			/* Exit status of the last command */
	int counter;		/* Counter for command execution */
} shell_data;

/* Function prototypes */

/* From exec_line.c */
int execute_line(shell_data *shell_data);

/* From environment.c (formerly env1.c) */
int compare_env_name(const char *env_var, const char *name);
char *get_environment_variable(const char *name, char **environ);
int print_environment(shell_data *shell_data);
int set_environment(shell_data *shell_data);
int unset_environment(shell_data *shell_data);

/* From env2.c */
char *copy_info(char *name, char *value);
void set_env(char *name, char *value, shell_data *shell_data);

/* From cmd_exec.c */
int is_cdir(char *path, int *i);
char *_which(char *cmd, char **_environ);
int is_executable(shell_data *shell_data);
int check_error_cmd(char *dir, shell_data *shell_data);
int execute_command(shell_data *shell_data);

/* From error_messages.c */
char *concatenate_cd_error(shell_data *shell_data,
char *msg, char *error, char *line_number);
char *cd_error_message(shell_data *shell_data);
char *not_found_error_message(shell_data *shell_data);
char *exit_shell_error_message(shell_data *shell_data);
char *environment_error_message(shell_data *shell_data);
char *path_error_message_126(shell_data *shell_data);

#endif /* SHELL_H */
