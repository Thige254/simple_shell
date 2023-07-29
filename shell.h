#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

extern char **environ;

char **read_command(void);
char **tokenize_command(char *line, char **tokens, int position);
void execute_command(char **args);
void shell_loop(void);

#endif /* SHELL_H */
