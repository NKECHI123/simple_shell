#include "shell.h"

/**
 * _strcat - concatenate two strings
 * @dest: char pointer to the destination of the copied string
 * @src: const char pointer to the source string
 * Return: the destination string
 */
char *_strcat(char *dest, const char *src)
{
	int i;
	int j;

	for (i = 0; dest[i] != '\0'; i++)
		;

	for (j = 0; src[j] != '\0'; j++)
	{
		dest[i] = src[j];
		i++;
	}

	dest[i] = '\0';
	return (dest);
}

/**
 * _strcpy - Copies the string pointed to by src.
 * @dest: char pointer to the destination of the copied string
 * @src: char pointer to the source string
 * Return: the destination string
 */
char *_strcpy(char *dest, char *src)
{
	size_t index;

	for (index = 0; src[index] != '\0'; index++)
	{
		dest[index] = src[index];
	}
	dest[index] = '\0';

	return (dest);
}

/**
 * _strcmp - Function that compares two strings.
 * @s1: string to be compared
 * @s2: string to be compared
 * Return: 0 if the strings are equal, a positive value if s1 > s2,
 *         a negative value if s1 < s2
 */
int _strcmp(char *s1, char *s2)
{
	int index;

	for (index = 0; s1[index] == s2[index] && s1[index]; index++)
		;

	if (s1[index] > s2[index])
		return (1);
	if (s1[index] < s2[index])
		return (-1);
	return (0);
}

/**
 * _strchr - locates a character in a string
 * @s: string to search in
 * @c: character to find
 * Return: a pointer to the first occurrence of the character
 *         c in the string s, or NULL if the character is not found
 */
char *_strchr(char *s, char c)
{
	unsigned int index = 0;

	for (; *(s + index) != '\0'; index++)
		if (*(s + index) == c)
			return (s + index);
	if (*(s + index) == c)
		return (s + index);
	return ('\0');
}

/**
 * _strspn - gets the length of a prefix substring
 * @s: initial segment
 * @accept: accepted bytes
 * Return: the number of accepted bytes
 */
int _strspn(char *s, char *accept)
{
	int i, j, found;

	for (i = 0; *(s + i) != '\0'; i++)
	{
		found = 1;
		for (j = 0; *(accept + j) != '\0'; j++)
		{
			if (*(s + i) == *(accept + j))
			{
				found = 0;
				break;
			}
		}
		if (found == 1)
			break;
	}
	return (i);
}
