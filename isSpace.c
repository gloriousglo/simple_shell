#include "shell.h"

/**
 * is_space - handle space commands
 * @buff: the command from the user
 * Return: return nothing
 */

bool is_space(char *buff)
{
	while (*buff)
	{
		if (!_isspace(*buff))
			return (false);
		buff++;
	}
	return (true);
}

/**
 * _isspace -  function to determine if a char is space
 * @ch: the character
 * Return: return 0 if it is a space an 1 otherwise
 */

int _isspace(int ch)
{
	return (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\v');
}
