#include "shell.h"

/**
 * _strncmp - Compares two strings up to n bytes.
 * @s1: The first string to compare.
 * @s2: The second string to compare.
 * @n: The number of bytes to compare.
 *
 * Return: If s1 < s2, a negative integer
 *         If s1 = s2, 0
 *         If s1 > s2, a positive integer.
 */
int _strncmp(char *s1, char *s2, size_t n)
{
	size_t i;

	for (i = 0; s1[i] && s2[i] && i < n; i++)
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
	}
	if (i == n)
		return (0);

	return (s1[i] - s2[i]);
}

/**
 * _strcpy - Copies the string pointed to by src,
 * including the null byte, to the buffer pointed to by dest.
 * @dest: The destination buffer.
 * @src: The source string.
 *
 * Return: The pointer to dest.
 */
char *_strcpy(char *dest, char *src)
{
	int i;

	for (i = 0; src[i] != '\0'; i++)
		dest[i] = src[i];

	dest[i] = '\0';

	return (dest);
}

/**
 * _strcat - Concatenates the string pointed to by src,
 * including the null byte, to the end of the string pointed to by dest.
 * @dest: The destination buffer.
 * @src: The source string.
 *
 * Return: The pointer to dest.
 */
char *_strcat(char *dest, char *src)
{
	int i, j;

	for (i = 0; dest[i] != '\0'; i++)
		;

	for (j = 0; src[j] != '\0'; j++)
		dest[i + j] = src[j];

	dest[i + j] = '\0';

	return (dest);
}

/**
 * _strncat - Concatenates the string pointed to by src,
 * including the null byte, to the end of the string pointed to by dest.
 * @dest: The destination buffer.
 * @src: The source string.
 * @n: The number of bytes to be used from src.
 *
 * Return: The pointer to dest.
 */
char *_strncat(char *dest, char *src, size_t n)
{
	int i, j;

	for (i = 0; dest[i] != '\0'; i++)
		;

	for (j = 0; src[j] != '\0' && j < (int)n; j++)
		dest[i + j] = src[j];

	dest[i + j] = '\0';

	return (dest);
}
