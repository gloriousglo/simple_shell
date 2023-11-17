#include "shell.h"

/**
 * getPATH - function to help get path from the environment
 * @env: environment variable
 * Return: return the path extacted
 */

char *getPATH(char **env)
{
	char *delim = "=";
	int i = 0;
	char **environ = env;
	char *pathKey, *pathValue, *path;

	while (environ[i] != NULL)
	{
		pathKey = strtok(environ[i], delim);
		pathValue = strtok(NULL, delim);

		if (pathKey != NULL && pathValue != NULL && _strcmp(pathKey, "PATH") == 0)
		{
			path = pathValue;
			return (path);
		}
		i++;
	}
	return (NULL);
}

/**
 * rightPath - Function to provide us with the
 * right path for execution inside execve
 * @arg: command entered by the user
 * Return: return the right command that can be executed
 */
char *rightPath(char *arg)
{
	char *path = getenv("PATH");
	char *exe, *dir, *path_cp, *command;

	if (path)
	{
		if (access(arg, X_OK) == 0)
			return (arg);
		path_cp = path;
		dir = strtok(path_cp, ":");

		while (dir)
		{
			exe = Cstrcat(dir, arg);
			if (access(exe, X_OK) == 0)
			{
				command = exe;
				return (command);
				free(exe);
			}
			free(exe);
			dir = strtok(NULL, ":");
		}
	}
	return (NULL);
}
