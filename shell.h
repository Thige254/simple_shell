#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define BUF_SIZE 1024

/* Define the structure for linked list nodes */
typedef struct list_s
{
	char *str;
	struct list_s *next;
} list_t;

/* Define the structure for storing information */
typedef struct
{
	list_t *environ;
	int env_changed;
	/* other fields needing tracking will be added here by you */
} info_t;

/* Function declarations */
char *display_prompt(void);
char **tokenize_input(char *input);
char *find_executable(char *command);
void handle_exit(char **tokens);
void handle_env(void);
char *custom_getline(void);
void handle_setenv(info_t *info, char **tokens);
void handle_unsetenv(info_t *info, char **tokens);

/* Function declarations for environment functions */
int _setenv(info_t *info, char *var, char *value);
int _unsetenv(info_t *info, char *var);

/* Function declarations for list operations */
char *starts_with(const char *str, const char *prefix);
void add_node_end(list_t **head, const char *str, int env_changed);
int delete_node_at_index(list_t **head, size_t index);

/* External variable for environment */
extern char **environ;

#endif /* _SHELL_H_ */
