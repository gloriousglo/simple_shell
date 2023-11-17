#include "shell.h"

/**
 * checkexe - function to check the other commands can be executed
 * @argsC: array of commands
 * @argv: description in execmd
 * @env: description in execmd
 * Return: retun 0 on success and -1 on failure
 */

int checkexe(char **argsC, char **argv, char **env)
{
	int i = 0, execmd = 0, n = 0;
	char *path;
	char *args[2];

	if (access(argsC[i], X_OK) == 0)
	{
		while (argsC[i] != NULL)
		{
			path = rightPath(argsC[i]);
			if (access(path, X_OK) == 0)
			{
				execmd++;
			}
			i++;
		}
		while (n < execmd)
		{
			args[0] = argsC[n];
			args[1] = NULL;
			exeCmd(args, argv, env);
			n++;
		}
	}
	else
		exeCmd(argsC, argv, env);
	return (0);
}
