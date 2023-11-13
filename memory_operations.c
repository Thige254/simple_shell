#include "shell.h"

/**
 * custom_memcpy - Copies information between void pointers.
 * @new_ptr: Destination pointer.
 * @ptr: Source pointer.
 * @size: Size of the new pointer.
 *
 * Return: No return.
 */
void custom_memcpy(void *new_ptr, const void *ptr, unsigned int size)
{
	char *char_ptr = (char *)ptr;
	char *char_new_ptr = (char *)new_ptr;
	unsigned int i;

	for (i = 0; i < size; i++)
		char_new_ptr[i] = char_ptr[i];
}

/**
 * custom_realloc - Reallocates a memory block.
 * @ptr: Pointer to the memory previously allocated.
 * @old_size: Size, in bytes, of the allocated space of ptr.
 * @new_size: New size, in bytes, of the new memory block.
 *
 * Return: ptr.
 * if new_size == old_size, returns ptr without changes.
 * if malloc fails, returns NULL.
 */
void *custom_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
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
		custom_memcpy(new_ptr, ptr, new_size);
	else
		custom_memcpy(new_ptr, ptr, old_size);

	free(ptr);
	return (new_ptr);
}

/**
 * custom_realloc_double_pointer - Reallocates a
 * memory block of a double pointer.
 * @ptr: Double pointer to the memory previously allocated.
 * @old_size: Size, in bytes, of the allocated space of ptr.
 * @new_size: New size, in bytes, of the new memory block.
 *
 * Return: ptr.
 * if new_size == old_size, returns ptr without changes.
 * if malloc fails, returns NULL.
 */
char **custom_realloc_double_pointer(char **ptr,
unsigned int old_size, unsigned int new_size)
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
