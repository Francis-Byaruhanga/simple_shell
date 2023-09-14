#include "shell.h"

/**
 * execute_command - Executes a command with arguments in a child process.
 *
 * @args: An array of strings representing the command and its arguments.
 *
 * Return: 0 on successful execution, -1 on error.
 */
int execute_command(char **args)
{
	pid_t pid;
	int status;

	if (args[0] == NULL)
		return (0);

	if (strcmp(args[0], "exit") == 0)
	{
		return (builtin_exit(args));
	}
	else if (strcmp(args[0], "env") == 0)
	{
		return (builtin_env(args));
	}

	if (!is_executable(args[0]))
	{
		fprintf(stderr, "%s: command not found\n", args[0]);
		return (-1);
	}

	pid = fork();

	if (pid == -1)
	{
		perror("fork");
		return (-1);
	}

	if (pid == 0)
	{
		if (execve(args[0], args, NULL) == -1)
		{
			perror("execve");
			return (-1);
		}
	}
	else
	{
		wait(&status);
		return (0);
	}
}

/**
 * builtin_env - Prints the current environment varibales.
 *
 * @args: An array of strings representing the command and its arguments.
 *
 * Return: Always 0 (Success).
 */
int builtin_env(char **args)
{
	char **env = environ;

	while (*env)
	{
		printf("%s\n", *env);
		env++;
	}

	return (0);
}
