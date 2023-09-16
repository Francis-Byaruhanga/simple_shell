#include "shell.h"

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
