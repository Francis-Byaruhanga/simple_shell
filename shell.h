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
#define MAX_ARGS 64
#define MAX_ARG_LENGTH 128

/* Function Prototypes */
void prompt_user(void);
char *read_input(void);
char **parse_input(char *input);
int execute_command(char **args);
int is_executable(const char *filename);
int builtin_env(char **args);
char *get_input(void);
int builtin_exit(char **args);

#endif /* SHELL_H */
