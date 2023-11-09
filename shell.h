#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h> /*Added for malloc, free, and exit */
#include <string.h> /* Added for strtok */
#include <errno.h>	/* Added for perror */

#define BUF_SIZE 1024

/* Function declarations */
char *display_prompt(void);
char **tokenize_input(char *input);
char *find_executable(char *command);

#endif /* _SHELL_H_ */
