#include "shell.h"

/**
 * _strcmp - the strcmp clone
 * @str1: string 1
 * @str2: string 2
 * Return: return 0 on success
 */

int _strcmp(const char *str1, const char *str2)
{
	while (*str1 != '\0' || *str2 != '\0')
	{
		if (*str1 < *str2)
			return (-1);
		str1++;
		str2++;
	}
	return (0);
}
