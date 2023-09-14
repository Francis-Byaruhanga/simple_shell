#include "shell.h"

/**
 * builtin_exit - Exit the shell with an optional status code.
 * @args: An array of strings representing the command and its arguments.
 *
 * Return: -1 if the shell should continue, or exit status if the shell
 *	should exit.
 */
int builtin_exit(char **args)
{
	int status = 0;

	if (args[1] != NULL)
	{
		status = atoi(args[1]);
	}

	exit(status);
}
