#include "shell.h"

/**
 * prompt - our shell prompt
 * Return: return 0 on success
 */

int prompt(void)
{
	char *str = "(£) ";

	if (isatty(0))
		prints(str);
	return (0);
}
