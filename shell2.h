#ifndef SHELL_H
#define SHELL_H

/* Required standard libraries */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/stat.h>

/* Global variable for the environment */
extern char **environ;

/* Function prototypes */
char *read_command(void);
void shell_loop(void);
char *get_cmd_path(char *cmd);

#endif /* SHELL_H */
