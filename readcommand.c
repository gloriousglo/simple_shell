i#include "shell.h"

/**
 * readCommand - Function to take users input
 *
 * Return: return number of characters read from the standard input
 */

char *readCommand(void)
{
	size_t n = 0;
	char *buff = NULL;
	int size;

	size = getline(&buff, &n, stdin);
	if (size == -1)
	{
		if (feof(stdin))
		{
			free(buff);
			exit(0);
		}
		else
			perror("Failed to read user input");
		free(buff);
	}

	return (buff);
}
