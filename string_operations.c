/* File: string_operations.c */
#include "shell.h"

/**
 * _str_concat - Concatenate two strings
 * @destination: Pointer to the destination string
 * @source: Pointer to the source string
 * Return: Pointer to the destination string
 */
char *_str_concat(char *destination, const char *source)
{
	int dest_len, src_index;

	for (dest_len = 0; destination[dest_len] != '\0'; dest_len++)
		;

	for (src_index = 0; source[src_index] != '\0'; src_index++)
	{
		destination[dest_len] = source[src_index];
		dest_len++;
	}

	destination[dest_len] = '\0';
	return (destination);
}

/**
 * _str_copy - Copy a string
 * @destination: Pointer to the destination string
 * @source: Pointer to the source string
 * Return: Pointer to the destination string
 */
char *_str_copy(char *destination, char *source)
{
	size_t index;

	for (index = 0; source[index] != '\0'; index++)
	{
		destination[index] = source[index];
	}
	destination[index] = '\0';

	return (destination);
}

/**
 * _str_compare - Compare two strings
 * @str1: First string to be compared
 * @str2: Second string to be compared
 * Return: 0 if equal, 1 if str1 is greater, -1 if str2 is greater
 */
int _str_compare(char *str1, char *str2)
{
	int index;

	for (index = 0; str1[index] == str2[index] && str1[index]; index++)
		;

	if (str1[index] > str2[index])
		return (1);
	if (str1[index] < str2[index])
		return (-1);
	return (0);
}

/**
 * _str_find_char - Locate a character in a string
 * @str: String to be searched
 * @character: Character to be located
 * Return: Pointer to the first occurrence of the
 * character, or '\0' if not found
 */
char *_str_find_char(char *str, char character)
{
	unsigned int index = 0;

	for (; *(str + index) != '\0'; index++)
		if (*(str + index) == character)
			return (str + index);

	if (*(str + index) == character)
		return (str + index);

	return ('\0');
}

/**
 * _str_span - Get the length of a prefix substring
 * @str: Initial segment
 * @accepted_chars: Accepted characters
 * Return: Number of accepted characters
 */
int _str_span(char *str, char *accepted_chars)
{
	int str_index, accepted_index, is_accepted;

	for (str_index = 0; *(str + str_index) != '\0'; str_index++)
	{
		is_accepted = 1;

		for (accepted_index = 0; *(accepted_chars
		+ accepted_index) != '\0'; accepted_index++)
		{
			if (*(str + str_index) == *(accepted_chars + accepted_index))
			{
				is_accepted = 0;
				break;
			}
		}

		if (is_accepted == 1)
			break;
	}

	return (str_index);
}
