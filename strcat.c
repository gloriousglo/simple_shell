/**
 * _strcat - function to concatenate
 * @str1: first string
 * @str2: second string
 * Return: return concatenated string
 */

#include "shell.h"

char *_strcat(const char *str1, const char *str2)
{
	int len1 = 0, len2 = 0, i;
	char *result;

	while (str1[len1] != '\0')
		len1++;
	while (str1[len2] != '\0')
		len2++;

	result = malloc(len1 + len2);

	if (result == NULL)
	{
		perror("Memory allocation failed");
		exit(0);
	}

	for (i = 0; i < len1; i++)
		result[i] = str1[i];
	for (i = 0; i < len2; i++)
		result[len1 + i] = str2[i];

	result[len1 + len2] = '\0';

	return (result);
}
