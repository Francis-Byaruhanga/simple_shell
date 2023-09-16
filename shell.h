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
#define WEXITSTATUS(status) (((status) & 0xFF00) >> 8)

/* Structs */
struct Alias {
	char *name;
	char *value;
	struct Alias *next;
};

/* Function Prototypes */
void prompt_user(void);
char *read_input(void);
char **parse_input(char *input);
int execute_command(char *command);
int is_executable(const char *filename);
int builtin_env(char **args);
char *get_input(void);
int builtin_exit(char **args);
int builtin_setenv(char **args);
int builtin_unsetenv(char **args);
int builtin_cd(char **args);
void alias_command(char **args);
void free_aliases(void);
char *replace_variables(char *command);
int main(int argc, char *argv[]);

#endif /* SHELL_H */
