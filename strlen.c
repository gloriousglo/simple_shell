#include "shell.h"

/**
 * _strlen - function to count the lenght of a string
 * @str: string whose lengh is to be counted
 * Return: return the numbers of char
 */

int _strlen(char *str)
{
	int i = 0;

	while (str[i] != '\0')
		i++;

	return (i);
}
