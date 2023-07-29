#ifndef SHELL_H
#define SHELL_H

/* Standard Libraries */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/stat.h>

extern char **environ;

/* Function Prototypes */
char *read_command(void);
void shell_loop(void);
char *get_cmd_path(char *cmd);

#endif /* SHELL_H */
