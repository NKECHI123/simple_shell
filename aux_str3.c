#include "shell.h"

/**
 * rev_str - reverses a string.
 * @str: input string.
 * Return: no return.
 */
void rev_str(char *str)
{
	int length = 0, i, j;
	char *s, temp;

	while (length >= 0)
	{
		if (str[length] == '\0')
			break;
		length++;
	}
	s = str;

	for (i = 0; i < (length - 1); i++)
	{
		for (j = i + 1; j > 0; j--)
		{
			temp = *(s + j);
			*(s + j) = *(s + (j - 1));
			*(s + (j - 1)) = temp;
		}
	}
}
