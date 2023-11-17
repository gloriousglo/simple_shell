#include "shell.h"

/**
 * prints - our printing function
 * @str: string to be printed
 * Return: return the numbers of characters
 */

int prints(char *str)
{
	int strCount = 0;

	while (str[strCount] != '\0')
		strCount++;
	write(STDOUT_FILENO, str, strCount);

	return (strCount);
}
