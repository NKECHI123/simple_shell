#include "shell.h"

/**
 * _strdup - duplicates a string in heap memory.
 * @str: const char pointer to the string
 * Return: duplicated string
 */
char *_strdup(const char *str)
{
	char *new_str;
	size_t length;

	length = _strlen(str);
	new_str = malloc(sizeof(char) * (length + 1));
	if (new_str == NULL)
		return (NULL);
	_memcopy(new_str, str, length + 1);
	return (new_str);
}

/**
 * _strlen - Returns the length of a string.
 * @str: const char pointer to the string
 * Return: length of the string
 */
int _strlen(const char *str)
{
	int length;

	for (length = 0; str[length] != '\0'; length++)
		;
	return (length);
}

/**
 * cmp_chars - compare characters of strings
 * @string: input string
 * @delim: delimiter
 *
 * Return: 1 if the characters are equal, 0 if not
 */
int cmp_chars(char string[], const char *delim)
{
	unsigned int i, j, count;

	for (i = 0, count = 0; string[i]; i++)
	{
		for (j = 0; delim[j]; j++)
		{
			if (string[i] == delim[j])
			{
				count++;
				break;
			}
		}
	}
	if (i == count)
		return (1);
	return (0);
}

/**
 * _strtok - splits a string by a delimiter
 * @string: input string
 * @delim: delimiter
 *
 * Return: the next token in the string
 */
char *_strtok(char string[], const char *delim)
{
	static char *split, *end;
	char *start;
	unsigned int i, bool;

	if (string != NULL)
	{
		if (cmp_chars(string, delim))
			return (NULL);
		split = string; /* Store first address */
		i = _strlen(string);
		end = &string[i]; /* Store last address */
	}
	start = split;
	if (start == end) /* Reaching the end */
		return (NULL);

	for (bool = 0; *split; split++)
	{
		/* Breaking loop and finding the next token */
		if (split != start)
			if (*split && *(split - 1) == '\0')
				break;
		/* Replacing delimiter with null character */
		for (i = 0; delim[i]; i++)
		{
			if (*split == delim[i])
			{
				*split = '\0';
				if (split == start)
					start++;
				break;
			}
		}
		if (bool == 0 && *split) /* String != Delimiter */
			bool = 1;
	}
	if (bool == 0) /* String == Delimiter */
		return (NULL);
	return (start);
}

/**
 * _isdigit - defines if a string is a number
 * @str: const char pointer to the string
 * Return: 1 if the string is a number, 0 otherwise
 */
int _isdigit(const char *str)
{
	unsigned int i;

	for (i = 0; str[i]; i++)
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
	}
	return (1);
}
