#include "shell.h"

/**
 * get_input - Read a line of input from the user.
 *
 * Return: A pointer to the input string, or NULL on EOF
 *	or error.
 */
char *get_input(void)
{
	static char buffer[1024];
	static size_t bufsize = 0;
	static ssize_t bytes_read = 0;

	char *input = NULL;
	ssize_t bytes;

	if (bytes_read == 0)
	{
		bytes = read(STDIN_FILENO, buffer, sizeof(buffer));

		if (bytes == -1)
		{
			perror("read");
			return (NULL);
		}
		if (bytes == 0)
		{
			return (NULL);
		}

		bufsize = (size_t)bytes;
		bytes_read = bytes;
	}

	char *newline = memchr(buffer, '\n', bytes_read);
	if (newline)
	{
		size_t length = (size_t)(newline - buffer) + 1;
		input = malloc(length);
		if (input == NULL)
		{
			perror("malloc");
			return (NULL);
		}

		memcpy(input, buffer, length);

		bytes_read -= length;
		memmove(buffer, buffer + length, bytes_read);
	}
	else
	{
		input = malloc(bufsize);
		if (input == NULL)
		{
			perror("malloc");
			return (NULL);
		}
		memcpy(input, buffer, bufsize);
		bytes_read = 0;
	}

	return (input);
}
