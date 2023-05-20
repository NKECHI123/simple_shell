#include "shell.h"

/**
 * read_line -  the input string.
 *
 * @i_eof: return the getline function value
 * Return: string input
 */
char *read_line(int *i_eof)
{
	char *input = NULL;
	size_t bufsize = 0;

	*i_eof = getline(&input, &bufsize, stdin);

	return (input);
}
