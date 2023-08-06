#include "shell.h"

/**
 * _atoi - Converts a string to an integer.
 * @s: The string to be converted.
 *
 * Return: The integer value of the string.
 */
int _atoi(char *s)
{
	int result = 0, sign = 1, start = 0, flag = 0;

	while (*(s + start))
	{
		if (*(s + start) == '-')
			sign *= -1;
		else if (*(s + start) >= '0' && *(s + start) <= '9')
		{
			result = result * 10 + *(s + start) - '0';
			flag = 1;
		}
		else if (flag == 1)
			break;
		start++;
	}

	return (sign * result);
}

/**
 * _itoa - Converts an integer to a string.
 * @n: The integer to be converted.
 *
 * Return: The string representation of the integer.
 */
char *_itoa(int n)
{
	int len = 0, temp = n, negative = 0;
	char *str;

	if (n < 0)
	{
		negative = 1;
		n *= -1;
		temp = n;
		len++;
	}

	while (temp)
	{
		len++;
		temp /= 10;
	}

	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);

	str[len] = '\0';

	while (len--)
	{
		str[len] = (negative && len == 0) ? '-' : (temp % 10) + '0';
		temp /= 10;
	}

	return (str);
}

/**
 * _strcmp - Compares two strings.
 * @s1: The first string to be compared.
 * @s2: The second string to be compared.
 *
 * Return: Difference of the two strings.
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}

	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

/**
 * _strncmp - Compares two strings.
 * @s1: The first string to be compared.
 * @s2: The second string to be compared.
 * @n: The number of characters to compare.
 *
 * Return: Difference of the two strings.
 */
int _strncmp(const char *s1, const char *s2, size_t n)
{
	if (n == 0)
		return (0);

	while (n-- && *s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}

	if (n == 0)
	{
		s1--;
		s2--;
	}

	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}
