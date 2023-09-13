#include "shell.h"

/**
 * **parse_input - Tokenises the input string into an array of arguments.
 * @input: The input string to be parsed.
 *
 * Return: An array of strings (arguments) or NULL on parsing error or memory
 *	allocation failure.
 */
char **parse_input(char *input)
{
	char **args = NULL;
	char *token;
	int arg_count = 0;
	int i;

	args = (char **)malloc(sizeof(char *) * MAX_ARGS);
	if (args == NULL)
	{
		perror("malloc");
		return (NULL);
	}

	token = strtok(input, " ");
	while (token != NULL)
	{
		args[arg_count] = (char *)malloc(sizeof(char) * (strlen(token) + 1));
		if (args[arg_count] == NULL)
		{
			perror("malloc");

			for (i = 0; i < arg_count; i++)
			{
				free(args[i]);
			}
			free(args);
			return (NULL);
		}

		strcpy(args[arg_count], token);

		token = strtok(NULL, " ");
		arg_count++;

		if (arg_count >= MAX_ARGS)
		{
			fprintf(stderr, "Too many arguments\n");

			for (i = 0; i < arg_count; i++)
			{
				free(args[i]);
			}
			free(args);
			return (NULL);
		}
	}

	args[arg_count] = NULL;

	return (args);
}
