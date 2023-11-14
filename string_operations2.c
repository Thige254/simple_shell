#include "shell.h"

/**
 * _str_duplicate - Duplicates a string in the heap memory.
 * @original: Type char pointer, the original string
 * Return: Duplicated string
 */
char *_str_duplicate(const char *original)
{
	char *duplicate;
	size_t length;

	length = _str_length(original);
	duplicate = malloc(sizeof(char) * (length + 1));
	if (duplicate == NULL)
		return (NULL);
	_memcpy(duplicate, original, length + 1);
	return (duplicate);
}

/**
 * _str_length - Returns the length of a string.
 * @s: Type char pointer
 * Return: Length of the string
 */
int _str_length(const char *s)
{
	int length;

	for (length = 0; s[length] != 0; length++)
	{
	}
	return (length);
}

/**
 * compare_chars - Compare characters of strings
 * @str: Input string.
 * @delim: Delimiter.
 *
 * Return: 1 if characters are equal, 0 if not.
 */
int compare_chars(char str[], const char *delim)
{
	unsigned int i, j, k;

	for (i = 0, k = 0; str[i]; i++)
	{
		for (j = 0; delim[j]; j++)
		{
			if (str[i] == delim[j])
			{
				k++;
				break;
			}
		}
	}
	if (i == k)
		return (1);
	return (0);
}

/**
 * _string_tokenize - Splits a string by some delimiter.
 * @str: Input string.
 * @delim: Delimiter.
 *
 * Return: Pointer to the tokenized string.
 */
char *_string_tokenize(char str[], const char *delim)
{
	static char *tokenized, *string_end;
	char *string_start;
	unsigned int i, bool;

	if (str != NULL)
	{
		if (compare_chars(str, delim))
			return (NULL);
		tokenized = str; /* Store the first address */
		i = _str_length(str);
		string_end = &str[i]; /* Store the last address */
	}
	string_start = tokenized;
	if (string_start == string_end) /* Reaching the end */
		return (NULL);

	for (bool = 0; *tokenized; tokenized++)
	{
		/* Breaking loop finding the next token */
		if (tokenized != string_start)
			if (*tokenized && *(tokenized - 1) == '\0')
				break;
		/* Replacing delimiter for null char */
		for (i = 0; delim[i]; i++)
		{
			if (*tokenized == delim[i])
			{
				*tokenized = '\0';
				if (tokenized == string_start)
					string_start++;
				break;
			}
		}
		if (bool == 0 && *tokenized) /* Str != Delim */
			bool = 1;
	}
	if (bool == 0) /* Str == Delim */
		return (NULL);
	return (string_start);
}

/**
 * _is_digit - Defines if the string passed is a number.
 *
 * @s: Input string
 * Return: 1 if the string is a number, 0 otherwise.
 */
int _is_digit(const char *s)
{
	unsigned int i;

	for (i = 0; s[i]; i++)
	{
		if (s[i] < '0' || s[i] > '9')
			return (0);
	}
	return (1);
}
