#include "shell.h"

/**
 * removeNewchar - Function to remove the newline character from user input
 * @str: user input
 * @len: length of the user input
 * Return: return the command without a newline character at the end
 */

char *removeNewchar(char *str, int len)
{
	if (_strcmp(str, "\n") == 0)
		return (str);
	if (len > 0 && str[len - 1] == '\n')
		str[len - 1] = '\0';

	return (str);
}
