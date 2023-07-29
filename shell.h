#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

void shell_loop(void);
char *read_command(void);
void execute_command(char *command);

#endif /* SHELL_H */
