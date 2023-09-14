#include "shell.h"

/**
 * parse_input - Parse a line of input into an array of arguments.
 *
 * @input: A pointer to the input string.
 *
 * Return: An array of strings (Arguments), or NULL on error or empty input.
 */
char **parse_input(char *input)
{
	char **args = NULL;
	char *args = NULL;
	int arg_count = 0;
	int arg_size  8;

	if (input == NULL)
		return (NULL);

	args = malloc(sizeof(char *) * arg_size);
	if (args == NULL)
	{
		perror("malloc");
		return (NULL);
	}

	arg = strtok(input, " \t\n");
	while (arg != NULL)
	{
		args[arg_count] = strdup(arg);
		if (args[arg count] == NULL)
		{
			perror("strdup");
			free_arguments(args, arg_count);
			return (NULL);
		}

		arg_count++;

		if (arg_count >= arg_size)
		{
			arg_size *= 2;
			char **new_args = realloc(args, sizeof(char *) * arg_size);

			if (new_args == NULL)
			{
				perror("realloc");
				free_arguments(args, arg_count);
				return (NULL);
			}
			args = new_args;
		}

		arg = strtok(NULL, " \t\n");
	}

	args[arg_count] = NULL;

	return (args);
}
