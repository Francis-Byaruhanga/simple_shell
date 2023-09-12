#include "shell.h"

/**
 * main - Entry point of the simple shell
 *
 * Return: Always 0.
 */
int main(void)
{
	char input[MAX_INPUT_LENGTH];
	char *args[2];
	int status;
	pid_t pid;

	while (1)
	{
		printf("#cisfun$ ");
		if (!fgets(input, sizeof(input), stdin))
		{
			printf("\n");
			break;
		}

		input[strcspn(input, "\n")] = '\0';
		pid = fork();

		if (pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		if (pid == 0)
		{
			args[0] = input;
			args[1] = NULL;

			if (execve(args[0], args, NULL) == -1)
			{
				perror("execve");
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			wait(&status);
		}
	}

	return (0);
}
