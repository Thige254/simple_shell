#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define BUF_SIZE 1024

/* Function declarations */
char *display_prompt(void);
char **tokenize_input(char *input);
char *find_executable(char *command);
void handle_exit(char **tokens);
void handle_env(void);
char *custom_getline(void);

/* External variable for environment */
extern char **environ;

#endif /* _SHELL_H_ */
