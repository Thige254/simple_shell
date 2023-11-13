#include "shell.h"

/**
 * custom_get_len - Get the length of a number.
 * @n: type int number.
 * Return: Length of a number.
 */
int custom_get_len(int n)
{
	unsigned int n1;
	int length = 1;

	if (n < 0)
	{
		length++;
		n1 = n * -1;
	}
	else
	{
		n1 = n;
	}
	while (n1 > 9)
	{
		length++;
		n1 = n1 / 10;
	}

	return (length);
}

/**
 * custom_itoa - function converts int to string.
 * @n: type int number
 * Return: String.
 */
char *custom_itoa(int n)
{
	unsigned int n1;
	int length = custom_get_len(n);
	char *buffer;

	buffer = malloc(sizeof(char) * (length + 1));
	if (buffer == 0)
		return (NULL);

	*(buffer + length) = '\0';

	if (n < 0)
	{
		n1 = n * -1;
		buffer[0] = '-';
	}
	else
	{
		n1 = n;
	}

	length--;
	do {
		*(buffer + length) = (n1 % 10) + '0';
		n1 = n1 / 10;
		length--;
	}
	while (n1 > 0);

	return (buffer);
}

/**
 * custom_atoi - converts a string to an integer.
 * @s: input string.
 * Return: integer.
 */
int custom_atoi(char *s)
{
	unsigned int count = 0, size = 0, result = 0, sign = 1, multiplier = 1, i;

	while (*(s + count) != '\0')
	{
		if (size > 0 && (*(s + count) < '0' || *(s + count) > '9'))
			break;

		if (*(s + count) == '-')
			sign *= -1;

		if ((*(s + count) >= '0') && (*(s + count) <= '9'))
		{
			if (size > 0)
				multiplier *= 10;
			size++;
		}
		count++;
	}

	for (i = count - size; i < count; i++)
	{
		result = result + ((*(s + i) - '0') * multiplier);
		multiplier /= 10;
	}
	return (result * sign);
}
