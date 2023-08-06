#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

/* Macros */
#define EXIT 2
#define END_OF_FILE 3

/* Data Structures */
typedef struct list_s list_t;
typedef struct alias_s alias_t;

/* Global Variables */
extern char **environ;
extern char *name;
extern int hist;
extern alias_t *aliases;

/* utilities functions */
int _atoi(char *s);
char *_itoa(int n);
int _strcmp(char *s1, char *s2);
int _strncmp(const char *s1, const char *s2, size_t n);

/* interpreter.c prototypes */
int (*get_builtin_func(char *s))(char **);
int hsh_cd(char **args);
int hsh_help(char **args);
int hsh_exit(char **args);
int hsh_env(char **args);
int hsh_setenv(char **args);
int hsh_unsetenv(char **args);
int hsh_alias(char **args);
int hsh_history(char **args);


int _print_env(void);
int _set_env(char **args);
int _unset_env(char **args);


char *get_command_path(char *cmd);
int execute_command(char **args, char **front, char *command,
int *exe_ret, int flag);


char **_getenv(char *name);
void free_env(void);
void _setenv(const char *name, const char *value, int overwrite);
void _unsetenv(const char *name);

/* utilities2.c */
int _strncmp(char *s1, char *s2, size_t n);
char *_strcpy(char *dest, char *src);
char *_strcat(char *dest, char *src);
char *_strncat(char *dest, char *src, size_t n);

/* utilities3.c */
void remove_comments(char *str);
int handle_line(char **line, size_t line_size);
int handle_args(int *exe_ret);

/* separator.c */
alias_t *add_alias_end(alias_t **head, char *name, char *value);
list_t *add_node_end(list_t **head, char *dir);
void free_alias_list(alias_t *head);
void free_list(list_t *head);

/* system_path.c */
char *get_location(char *command);
char *fill_path_dir(char *path);
list_t *get_path_dir(char *path);

/* sample utility functions */
char *path_join(const char *path1, const char *path2);
char **split_string(const char *str, const char *delim);
char *replace_string(const char *str, const char *old, const char *new);

/* arguments2.c */
int can_not_open_file(char *file_path);
int process_file_commands(char *file_path, int *exe_ret);

/* signal handler */
void sig_handler(int sig);

/* main */
int main(int argc, char *argv[]);

#endif /* SHELL_H */
