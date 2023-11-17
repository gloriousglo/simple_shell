#include "shell.h"

/**
 * Cstrcat - This function will help to concatenate the path and /
 * @str1: the command from the user
 * @str2: path
 * Return: return concatenates result
 */

char *Cstrcat(char *str1, char *str2)
{
	int len1 = _strlen(str1), len2 = _strlen(str2);
	char *result = malloc(len1 + len2 + 2);

	result = _strcat(str1, "/");
	result = _strcat(result, str2);
	result = _strcat(result, "\0");

	return (result);
}
