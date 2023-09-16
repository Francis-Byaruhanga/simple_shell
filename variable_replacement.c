#include "shell.h"

/**
 * replace_variables - Replace variables in a command string.
 * @command: The input command to process.
 *
 * Return: A pointer to a newly allocated string with variables replaced.
 *	on sucess, NULL if memory allocation fails.
 */
char *replace_variables(char *command)
{
	char *new_command = NULL;
	char *pos = command;
	char *start = NULL;

	while ((start = strstr(pos, "$$")) != NULL)
	{
		size_t len_before = start - command;
		size_t len_after = strlen(start + 2);
		size_t new_len = len_before + sizeof(pid_t) + len_after;

		new_command = (char *)malloc(new_len + 1);
		if (new_command == NULL)
		{
			perror("malloc");
			exit(EXIT_FAILURE);
		}

		strcpy(new_command, command, len_before);

		pid_t pid = getpid();

		snprintf(new_command + len_before, new_len - len_before, "%d", pid);
		strcpy(new_command + len_before + sizeof(pid_t) - 1, start + 2);
		pos = new_command + len_before + sizeof(pid_t) + len_after;
	}

	return (new_command ? new_command : strdup(command));
}
