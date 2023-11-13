#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <limits.h>

#define BUFSIZE 1024
#define TOK_BUFSIZE 128
#define TOK_DELIM " \t\r\n\a"

/* Points to an array of pointers to strings representing the "environment" */
extern char **environ;

/**
 * struct data_shell - Structure containing runtime data for the shell
 * @av: Array of strings representing the argument vector
 * @input: String representing the command line input by the user
 * @args: Array of strings representing tokens of the command line
 * @status: Integer representing the last status of the shell
 * @counter: Integer representing the line counter
 * @_environ: Array of strings representing environment variables
 * @pid: String representing the process ID of the shell
 */
typedef struct data_shell
{
	char **av;
	char *input;
	char **args;
	int status;
	int counter;
	char **_environ;
	char *pid;
} data_shell;

/**
 * struct sep_list_s - Single linked list for separators
 * @separator: Character representing ; | &
 * @next: Pointer to the next node in the list
 * Description: Single linked list structure to store separators
 */
typedef struct sep_list_s
{
	char separator;
	struct sep_list_s *next;
} sep_list;

/**
 * struct line_list_s - Single linked list for command lines
 * @line: String representing a command line
 * @next: Pointer to the next node in the list
 * Description: Single linked list structure to store command lines
 */
typedef struct line_list_s
{
	char *line;
	struct line_list_s *next;
} line_list;

/**
 * struct r_var_list - Single linked list for variables
 * @len_var: Length of the variable
 * @val: Value of the variable
 * @len_val: Length of the value
 * @next: Pointer to the next node in the list
 * Description: Single linked list structure to store variables
 */
typedef struct r_var_list
{
	int len_var;
	char *val;
	int len_val;
	struct r_var_list *next;
} r_var;

/**
 * struct builtin_s - Builtin struct for command args.
 * @name: String representing the name of the command
 * builtin (e.g., cd, exit, env)
 * @f: Function pointer
 */
typedef struct builtin_s
{
	char *name;
	int (*f)(data_shell *datash);
} builtin_t;

/**
 * Copies a string.
 */
char *_custom_strcpy(char *dest, const char *src);

/**
 * Concatenates two strings.
 */
char *_custom_strcat(char *dest, const char *src);

/**
 * Converts an integer to a string.
 */
char *_custom_itoa(int num);

/**
 * _reallocdp - reallocates memory for an array of pointers
 *
 * @ptr: pointer to the array of pointers to be reallocated
 * @old_size: old size of the array
 * @new_size: new size of the array
 *
 * Return: pointer to the reallocated array
 */
char **_reallocdp(char **ptr, size_t old_size, size_t new_size);

/*Setenv declaration*/
void set_env(const char *name, const char *value, data_shell *datash);

/* Reverse string declaration*/
void reverse_string(char *str);

/* itoa declaration*/
char *itoa(int num);

/* Variable_lists.c prototypes */
r_var *append_variable(r_var **head,
					   int length_var, char *value, int length_val);
void free_variable_list(r_var **head);

/* Declarations for functions used in syntax_error_handler.c */
int aux_itoa(int num);
size_t _strlen(const char *str);
void _strcpy(char *dest, const char *src);
void _strcat(char *dest, const char *src);

/* Declarations for functions in syntax_error_handler.c */
int count_repeated_char(char *input, int i);
int find_syntax_error(char *input, int i, char last);
int find_first_char(char *input, int *i);
void print_syntax_error_msg(data_shell *datash, char *input, int i, int bool);
int check_syntax_error(data_shell *datash, char *input);

/* string_operations.c prototypes */
char *custom_strcat(char *dest, const char *src);
char *custom_strcpy(char *dest, char *src);
int custom_strcmp(char *s1, char *s2);
char *custom_strchr(char *s, char c);
int custom_strspn(char *s, char *accept);

/* string_operations2.c prototypes */
char *custom_strdup(const char *s);
int custom_strlen(const char *s);
int compare_chars(char str[], const char *delim);
char *custom_strtok(char str[], const char *delim);
int custom_isdigit(const char *s);

/* memory_operations.c prototypes */
void custom_memcpy(void *new_ptr, const void *ptr, unsigned int size);
void *custom_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char **custom_realloc_double_pointer(char **ptr, unsigned int old_size,
									 unsigned int new_size);

/* string_conversions.c prototypes */
char *itoa(int num);
int custom_atoi(char *s);

/* Linked_lists.c prototypes */
sep_list *append_separator(sep_list **head, char separator);
void free_separator_list(sep_list **head);
line_list *append_line(line_list **head, char *line);
void free_line_list(line_list **head);

/* Custom function declarations help_info...*/
size_t _custom_strlen(const char *str);

/* help_info.c prototypes */
void display_env_help(void);
void display_setenv_help(void);
void display_unsetenv_help(void);
void display_general_help(void);
void display_exit_help(void);

/* error_handling.c prototypes */
char *concat_error_message(data_shell *shell_data,
						   char *msg, char *error_msg, char *line_str);
char *error_cd(data_shell *shell_data);
char *error_command_not_found(data_shell *shell_data);
char *error_exit_shell(data_shell *shell_data);

/* error_handling2.c prototypes */
char *handle_env_error(data_shell *shell_data);
char *handle_permission_error(data_shell *shell_data);

/* environment_command.c prototypes */
int compare_env_names(const char *env_var, const char *name);
char *get_environment_variable(const char *name, char **_environ);
int print_environment_variables(data_shell *datash);

/* environment_display.c prototypes */
char *duplicate_info(char *name, char *value);
void set_environment_variable(char *name, char *value, data_shell *datash);
int _set_environment(data_shell *datash);
int _unset_environment(data_shell *datash);

/* command_executor.c prototypes */
int is_current_directory(char *path, int *i);
char *find_command_location(char *cmd, char **_environ);
int determine_executable(data_shell *datash);
int verify_command_error(char *dir, data_shell *datash);
int execute_command(data_shell *datash);

/* Declare functions for command_executor.c file */
char *_getenv(const char *name, char **environ);
char *_strdup(const char *s);
char *_strtok(char *str, const char *delim);
void get_error(data_shell *datash, int error);
int _strcmp(const char *s1, const char *s2);

/* Change_directory.c prototypes */
void change_directory_parent(data_shell *datash);
void change_directory_to(data_shell *datash);
void change_directory_previous(data_shell *datash);
void change_directory_to_home(data_shell *datash);

/* New prototypes based on refactoring in change_directory.c */
void set_directory_variables(data_shell *datash, char *old_path,
							 char *new_path, int status);

/* change_directory_shell.c prototype */
int change_directory_shell(data_shell *datash);

#endif /* _SHELL_H_ */
