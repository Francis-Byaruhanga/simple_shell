#include "shell.h"

/**
 * read_input - Read a line of input from the user.
 *
 * Return: A pointer to the input string,or NULL on EOF or error.
 */
char *read_input(void)
{
	char *input = NULL;
	size_t bufsize = 0;

	if (getline(&input, &bufsize, stdin) == -1)
	{
		if (feof(stdin))
		{
			free(input);
			return (NULL);
		}
		perror("getline");
		exit(EXIT_FAILURE);
	}

	return (input);
}

/**
 * main - Entry point of the simple shell
 *
 * Return: Always 0.
 */
int main(void)
{
	char *input;
	char **args;
	int status;

	while (1)
	{
		printf("#cisfun$ ");
		input = read_input();
		if (!input)
		{
			printf("\n");
			break;
		}

		args = parse_input(input);
		if (args == NULL)
		{
			free(input);
			continue;
		}

		status = execute_command(args);

		free(input);
		free(args);

		if (status == -1)
			break;
	}

	return (0);
}
