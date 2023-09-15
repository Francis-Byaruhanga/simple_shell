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
	char **commands;
	int status = 0;

	while (1)
	{
		printf("#cisfun$ ");
		input = read_input();
		if (!input)
		{
			printf("\n");
			break;
		}

		commands = parse_input(input);
		if (commands == NULL)
		{
			free(input);
			continue;
		}

		for (int i = 0; commands[i] != NULL; i++)
		{
			if (strstr(commands[i], "alias") != NULL)
			{
				alias_command(commands[i]);
			}
			else if (status == 0 (status != 0 && strstr(commands[i], "&&") != NULL))
			{
				status = execute_command(commands[i]);
			}
			else if (status != && strstr(commands[i], "||") != NULL)
			{
				status = execute_command(commands[i]);
			}
		}

		free(input);
		free(commands);
	}

	free_aliases(void);

	return (0);
}
