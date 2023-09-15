#include "shell.h"

/**
 * parse_input - Parse the user's input into separate commands.
 * @input: The user's input string.
 *
 * Return: An array of strings, where each string represents a command.
 */
char **parse_input(char *input)
{
	char **commands = NULL;
	char *token;
	int i = 0;

	token = strtok(input, ";");
	while (token != NULL)
	{
		commands = realloc(commands, (i + 1) * sizeof(char *));
		if (commands == NULL)
		{
			perror("realloc");
			exit(EXIT_FAILURE);
		}

		commands[i] = strdup(token);
		if (commands[i] == NULL)
		{
			perror("strdup");
			exit(EXIT_FAILURE);
		}

		token = strtok(NULL, ";");
		i++;
	}

	commands = realloc(commands, (i + 1) * sizeof(char *));
	if (commands == NULL)
	{
		perror("realloc");
		exit(EXIT_FAILURE);
	}
	commands[i] = NULL;

	return (commands);
}
