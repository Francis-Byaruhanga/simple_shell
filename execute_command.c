#include "shell.h"

/**
 * execute_command - Executes a command with the provided arguments in
 * a child process
 * @args: An array of strings representing the command and its arguments
 *
 * Return: 0 on successful execution and -1 on error, such as fork or execve
 *	failure
 */
int execute_command(char **args)
{
	pid_t pid;
	int status;

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

	return (0);
}

/**
 * is_executable - Checks if a command is executable in one
 * of the Path directories
 *
 * @filename: The name of the command to check for executable
 *
 * Return: 1 if the command is executable, 0 otherwise
 */
int is_executable(const char *filename)
{
	char *path = getenv("PATH");
	char *token;
	char *path_copy = strdup(path);

	if (path == NULL)
	{
		fprintf(stderr, "PATH environment varibale is not set\n");
		return (0);
	}

	if (path_copy == NULL)
	{
		perror("strdup");
		return (0);
	}

	token = strtok(path_copy, ":");

	while (token != NULL)
	{
		char *full_path = malloc(strlen(token) + strlen(filename) + 2);

		if (full_path == NULL)
		{
			perror("malloc");
			free(path_copy);
			return (0);
		}
		sprintf(full_path, "%s/%s", token, filename);

		if (access(full_path, X_OK) == 0)
		{
			free(full_path);
			free(path_copy);
			return (1);
		}

		free(full_path);
		token = strtok(NULL, ":");
	}

	free(path_copy);
	return (0);
}
