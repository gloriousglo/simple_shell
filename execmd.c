#include "shell.h"

/**
 * exeCmd - function to execute userr command
 * @argsC: an array of commands from the user
 * @argv: argument vector
 * @env: environment variable
 * Return: return 0 om success
 */

int exeCmd(char *argsC[], char **argv, char **env)
{
	pid_t pid;
	int exe, status;
	char *command;

	pid = fork();

	if (pid == -1)
	{
		perror("Failed to create process");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		command = rightPath(argsC[0]);
		exe = execve(command, argsC, env);
		if (exe == -1)
		{
			perror(argv[0]);
			exit(EXIT_FAILURE);
		}
	}
	else
		wait(&status);

	return (0);
}
