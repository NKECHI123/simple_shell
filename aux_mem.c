#include "shell.h"

/**
 * _memcopy - copies information between void pointers.
 * @dest: destination pointer.
 * @src: source pointer.
 * @size: size of the destination pointer.
 *
 * Return: no return.
 */
void _memcopy(void *dest, const void *src, unsigned int size)
{
	char *char_dest = (char *)dest;
	char *char_src = (char *)src;
	unsigned int i;

	for (i = 0; i < size; i++)
		char_dest[i] = char_src[i];
}

/**
 * _realloc - reallocates a memory block.
 * @ptr: pointer to the memory previously allocated.
 * @old_size: size, in bytes, of the allocated space of ptr.
 * @new_size: new size, in bytes, of the new memory block.
 *
 * Return: ptr.
 * if new_size == old_size, returns ptr without changes.
 * if malloc fails, returns NULL.
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	void *new_ptr;

	if (ptr == NULL)
		return (malloc(new_size));

	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}

	if (new_size == old_size)
		return (ptr);

	new_ptr = malloc(new_size);
	if (new_ptr == NULL)
		return (NULL);

	if (new_size < old_size)
		_memcopy(new_ptr, ptr, new_size);
	else
		_memcopy(new_ptr, ptr, old_size);

	free(ptr);
	return (new_ptr);
}

/**
 * _reallocdp - reallocates a memory block of a double pointer.
 * @ptr: double pointer to the memory previously allocated.
 * @old_size: size, in bytes, of the allocated space of ptr.
 * @new_size: new size, in bytes, of the new memory block.
 *
 * Return: ptr.
 * if new_size == old_size, returns ptr without changes.
 * if malloc fails, returns NULL.
 */
char **_reallocdp(char **ptr, unsigned int old_size, unsigned int new_size)
{
	char **new_ptr;
	unsigned int i;

	if (ptr == NULL)
		return (malloc(sizeof(char *) * new_size));

	if (new_size == old_size)
		return (ptr);

	new_ptr = malloc(sizeof(char *) * new_size);
	if (new_ptr == NULL)
		return (NULL);

	for (i = 0; i < old_size; i++)
		new_ptr[i] = ptr[i];

	free(ptr);

	return (new_ptr);
}
