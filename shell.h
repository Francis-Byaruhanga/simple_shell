#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

/* Macros */
#define MAX_INPUT_LENGTH 100

/* Function Prototypes */
void prompt_user(void);

#endif /* SHELL_H */

