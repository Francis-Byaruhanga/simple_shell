#include "shell.h"

/**
 * read_input - Read a line of input from the user.
 *
 * Return: A pointer to the input string,or NULL on EOF or error.
 */
char *read_input(void)
{
	char *input = NULL;
	size_t len = 0;
	ssize_t read;

	printf("#cisfun$ ");
	read = getline(&input, &len, stdin);

	if (read == -1)
	{
		free(input);
		return (NULL);
	}

	if (input[0] == '#')
	{
		free(input);
		return (NULL);
	}

	if (input[read - 1] == '\n')
	{
		input[read - 1] = '\0';
	}

	return (input);
}

/**
 * main - Entry point of the simple shell.
 * @argc: The number of commandline arguments
 * @argv: An array of strings containing the commandline arguments.
 *
 * Return: The exit status of the shell program.
 */
int main(int argc, char *argv[])
{
	char *input;
	char **commands;
	int status = 0;

	if (argc == 2)
	{
		FILE *file = fopen(argv[1], "r");

		if (!file)
		{
			perror("Error opening file");
			return (1);
		}

		char line[1024];

		while (fgets(line, sizeof(line), file))
		{
			line[strcspn(line, "\n")] = '\0';

			commands = parse_input(line);
			if (commands == NULL)
			continue;

			for (int i = 0; commands[i] != NULL; i++)
			{
				if (status == 0 || (status != 0 && strstr(commands[i], "&&") != NULL))
				{
					status = execute_command(commands[i]);
				}
				else if (status != 0 && strstr(commands[i], "||") != NULL)
				{
					status = execute_command(commands[i]);
				}
			}

			free(commands);
		}

		fclose(file);
	}
	else
	{
		while (1)
		{
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
				if (status == 0 || (status != 0 && strstr(commands[i], "&&") != NULL))
				{
					status = execute_command(commands[i]);
				}
				else if (status != 0 && strstr(commands[i], "||") != NULL)
				{
					status = execute_command(commands[i]);
				}
			}

			free(input);
			free(commands);
		}
	}

	return (status);

}
