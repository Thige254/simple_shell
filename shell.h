#ifndef SHELL_H
#define SHELL_H

/* Standard Libraries */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

/* Function Prototypes */
char *read_command(void);
char *get_cmd_path(char *cmd);
void shell_loop(void);

#endif /* SHELL_H */
