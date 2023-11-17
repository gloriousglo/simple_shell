#include "shell.h"

/**
 * changeDirectory - function to handle change directory
 * @var: array of commands
 * Return: return 0 on success and -1 if otherwise
 */

int changeDirectory(char **var)
{
	const char *path = rightPath(var[1]);
	char current_path[PATH_MAX];
	int cd;

	if (getcwd(current_path, PATH_MAX) == NULL)
	{
		perror("error could'nt get current directory");
		return (1);
	}

	cd = chdir(path);
	if (cd == -1)
	{
		perror("directory does not exist");
		return (1);
	}
	return (0);
}
