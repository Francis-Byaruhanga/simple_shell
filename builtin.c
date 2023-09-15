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
	else if (strcmp(args[0], "setenv") == 0)
	{
		return (builtin_setenv(args));
	}
	else if (strcmp(args[0], "unsetenv") == 0)
	{
		return (builtin_unsetenv(args));
	}
	else if (strcmp(args[0], "cd") == 0)
	{
		return (builtin_cd(args));
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

/**
 * builtin_setenv - Set or modify an environment variable.
 * @args: An array of strings representing the command and its arguments.
 *
 * Return: 0 on success, -1 on faliure.
 */
int builtin_setenv(char **args)
{
	if (args[1] == NULL || args[2] == NULL)
	{
		fprintf(stderr, "Usage: setenv VARIABLE VALUE\n");
		return (-1);
	}

	if (setenv(args[1], args[2], 1) == -1)
	{
		perror("sentenv");
		return (-1);
	}

	return (0);
}

/**
 * builtin_unsetenv - Unset an environment variable.
 * @args: An array of strings representing the command and its arguments.
 *
 * Return: 0 on success, -1 on failure.
 */
int builtin_unsetenv(char **args)
{
	if (args[1] == NULL)
	{
		fprintf(stderr, "Usage: unsetenv VARIABLE\n");
		return (-1);
	}

	if (unsetenv(args[1]) == -1)
	{
		perror("unsetenv");
		return (-1);
	}

	return (0);
}

/**
 * builtin_cd - Change the current directory.
 * @args: An array of strings representing the command and its arguments.
 *
 * Return: 0 on success, -1 on failure.
 */
int builtin_cd(char **args)
{
	char *new_dir;

	if (args[1] == NULL || strcmp(args[1], "~") == 0)
	{
		new_dir == getenv("HOME");
		if (new_dir == NULL)
		{
			fprintf(stderr, "cd: HOME not set\n");
			return (-1);
		}
	}
	else if (strcmp(args[1], "-") == 0)
	{
		new_dir = getenv("OLDPWD");
		if (new_dir == NULL)
		{
			fprintf(stderr, "cd: OLDPWD not set\n");
			return (-1);
		}
	}
	else
	{
		new_dir = args[1];
	}

	char *current_dir = getcwd(NULL, 0);

	if (current_dir == NULL)
	{
		perror("getcwd");
		return (-1);
	}

	if (chdir(new_dir) == -1)
	{
		perror("chdir");
		free(current_dir);
		return (-1);
	}

	if (setenv("OLDPWD", current_dir, 1) == -1 || setenv("PWD", new_dir, 1) == -1)
	{
		perror("setenv");
		free(current_dir);
		return (-1);
	}

	free(current_dir);
	return (0);
}
