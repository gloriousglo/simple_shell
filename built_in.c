#include "shell.h"

/**
 * built_in - function to help with built in functions
 * @var: variable conatining the built_in function
 * @buff: buffer containing space to be freed
 * @env: environment variable
 * Return: return 0 on success
 */

int built_in(char **var, char *buff, char **env)
{
	char *str;
	int status, count = 0, i = 0;

	while (var[count] != NULL)
		count++;

	if (_strcmp(var[0], "exit") == 0)
	{
		if (count > 1)
		{
			status = strtol(var[1], &str, 10);
			free(buff);
			exit(status);
		}
		else
		{
			free(buff);
			exit(0);
		}
	}

	if (_strcmp(var[0], "env") == 0)
	{
		while (env[i] != NULL)
		{
			prints(env[i]);
			putchar('\n');
			i++;
		}
	}
	return (0);
}
