#include "shell.h"

struct Alias *alias_list = NULL;

/**
 * alias_command - Handle the alias built-in command.
 *
 * @args: An array of strings containing the command-line arguments.
 *
 * Return: 0 on Success.
 */
int alias_command(char **args)
{
	struct Alias *new_alias;

	if (args[1] == NULL)
	{
		struct Alias *current = alias_list;

		while (current != NULL)
		{
			printf("%s='%s'\n", current->name, current->value);
			current = current->next;
		}
	}
	else if (args[2] == NULL)
	{
		struct Alias *current = alias_list;

		while (current != NULL)
		{
			if (strcmp(current->name, args[1]) == 0)
			{
				printf("%s='%s'\n", current->name, current->value);
				return (0);
			}
			current = current->next;
		}
	}
	else
	{
		char *name = args[1];
		char *value = args[2];

		struct Alias *current = alias_list;

		while (current != NULL)
		{
			if (strcmp(current->name, name) == 0)
			{
				free(current->value);
				current->value = strdup(value);
				return (0);
			}
			current = current->next;
		}

		new_alias = (struct Alias *)malloc(sizeof(struct Alias));

		if (new_alias == NULL)
		{
			perror("malloc");
			exit(EXIT_FAILURE);
		}

		new_alias->name = strdup(name);
		new_alias->value = strdup(value);
		new_alias->next = alias_list;
		alias_list = new_alias;
	}

	return (0);
}

/**
 * free_aliases - Free memory allocated for alias list.
 */
void free_aliases(void)
{
	struct Alias *current = alias_list;

	while (current != NULL)
	{
		struct Alias *next = current->next;

		free(current->name);
		free(current->value);
		free(current);
		current = next;
	}
}
