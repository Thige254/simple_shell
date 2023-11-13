#include "shell.h"

/**
 * custom_strcat - Concatenate two strings.
 * @dest: Destination string.
 * @src: Source string.
 * Return: Pointer to the destination string.
 */
char *custom_strcat(char *dest, const char *src)
{
	int dest_index, src_index;

	for (dest_index = 0; dest[dest_index] != '\0'; dest_index++)
		;

	for (src_index = 0; src[src_index] != '\0'; src_index++)
	{
		dest[dest_index] = src[src_index];
		dest_index++;
	}

	dest[dest_index] = '\0';
	return (dest);
}

/**
 * custom_strcpy - Copy the string pointed to by src.
 * @dest: Destination string.
 * @src: Source string.
 * Return: Pointer to the destination string.
 */
char *custom_strcpy(char *dest, char *src)
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
 * custom_strcmp - Compare two strings.
 * @s1: String to be compared.
 * @s2: String to be compared.
 * Return: 0 if the strings are equal, a negative value if s1 < s2,
 * a positive value if s1 > s2.
 */
int custom_strcmp(char *s1, char *s2)
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
 * custom_strchr - Locate a character in a string.
 * @s: String.
 * @c: Character.
 * Return: Pointer to the first occurrence of the character c.
 */
char *custom_strchr(char *s, char c)
{
	unsigned int index = 0;

	for (; *(s + index) != '\0'; index++)
		if (*(s + index) == c)
			return (s + index);
	if (*(s + index) == c)
		return (s + index);
	return (NULL);
}

/**
 * custom_strspn - Get the length of a prefix substring.
 * @s: Initial segment.
 * @accept: Accepted bytes.
 * Return: The number of accepted bytes.
 */
int custom_strspn(char *s, char *accept)
{
	int s_index, accept_index, is_accepted;

	for (s_index = 0; *(s + s_index) != '\0'; s_index++)
	{
		is_accepted = 1;
		for (accept_index = 0; *(accept + accept_index) != '\0'; accept_index++)
		{
			if (*(s + s_index) == *(accept + accept_index))
			{
				is_accepted = 0;
				break;
			}
		}
		if (is_accepted == 1)
			break;
	}
	return (s_index);
}
