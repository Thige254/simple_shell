#include "shell.h"

/**
 * custom_strdup - Duplicates a string in the heap memory.
 * @s: Source string.
 * Return: Duplicated string.
 */
char *custom_strdup(const char *s)
{
	char *duplicate;
	size_t len;

	len = custom_strlen(s);
	duplicate = malloc(sizeof(char) * (len + 1));
	if (duplicate == NULL)
		return (NULL);
	custom_memcpy(duplicate, s, len + 1);
	return (duplicate);
}

/**
 * custom_strlen - Returns the length of a string.
 * @s: Source string.
 * Return: Length of the string.
 */
int custom_strlen(const char *s)
{
	int len;

	for (len = 0; s[len] != 0; len++)
	{
	}
	return (len);
}

/**
 * compare_chars - Compare characters of strings.
 * @str: Input string.
 * @delim: Delimiter.
 * Return: 1 if the characters are equal, 0 if not.
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
 * custom_strtok - Splits a string by some delimiter.
 * @str: Input string.
 * @delim: Delimiter.
 * Return: String split.
 */
char *custom_strtok(char str[], const char *delim)
{
	static char *splitted, *str_end;
	char *str_start;
	unsigned int i, bool;

	if (str != NULL)
	{
		if (compare_chars(str, delim))
			return (NULL);
		splitted = str; /* Store the first address */
		i = custom_strlen(str);
		str_end = &str[i]; /* Store the last address */
	}
	str_start = splitted;
	if (str_start == str_end) /* Reaching the end */
		return (NULL);

	for (bool = 0; *splitted; splitted++)
	{
		/* Breaking the loop finding the next token */
		if (splitted != str_start)
			if (*splitted && *(splitted - 1) == '\0')
				break;
		/* Replacing delimiter with null char */
		for (i = 0; delim[i]; i++)
		{
			if (*splitted == delim[i])
			{
				*splitted = '\0';
				if (splitted == str_start)
					str_start++;
				break;
			}
		}
		if (bool == 0 && *splitted) /* Str != Delim */
			bool = 1;
	}
	if (bool == 0) /* Str == Delim */
		return (NULL);
	return (str_start);
}

/**
 * custom_isdigit - Defines if the string passed is a number.
 * @s: Input string.
 * Return: 1 if the string is a number, 0 otherwise.
 */
int custom_isdigit(const char *s)
{
	unsigned int i;

	for (i = 0; s[i]; i++)
	{
		if (s[i] < '0' || s[i] > '9')
			return (0);
	}
	return (1);
}
