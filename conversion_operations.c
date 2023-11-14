#include "main.h"

/**
 * num_length - Get the length of a number.
 * @num: Integer number.
 * Return: Length of the number.
 */
int num_length(int num)
{
	unsigned int num_copy;
	int length = 1;

	if (num < 0)
	{
		length++;
		num_copy = num * -1;
	}
	else
	{
		num_copy = num;
	}

	while (num_copy > 9)
	{
		length++;
		num_copy = num_copy / 10;
	}

	return (length);
}

/**
 * int_to_str - Convert integer to string.
 * @num: Integer number.
 * Return: String representation.
 */
char *int_to_str(int num)
{
	unsigned int num_copy;
	int length = num_length(num);
	char *buffer;

	buffer = malloc(sizeof(char) * (length + 1));
	if (buffer == NULL)
		return (NULL);

	*(buffer + length) = '\0';

	if (num < 0)
	{
		num_copy = num * -1;
		buffer[0] = '-';
	}
	else
	{
		num_copy = num;
	}

	length--;

	do {
		*(buffer + length) = (num_copy % 10) + '0';
		num_copy = num_copy / 10;
		length--;
	} while (num_copy > 0);

	return (buffer);
}

/**
 * str_to_int - Convert a string to an integer.
 * @str: Input string.
 * Return: Integer.
 */
int str_to_int(char *str)
{
	unsigned int count = 0, size = 0, result = 0, sign = 1, multiplier = 1, i;

	while (*(str + count) != '\0')
	{
		if (size > 0 && (*(str + count) < '0' || *(str + count) > '9'))
			break;

		if (*(str + count) == '-')
			sign *= -1;

		if ((*(str + count) >= '0') && (*(str + count) <= '9'))
		{
			if (size > 0)
				multiplier *= 10;
			size++;
		}
		count++;
	}

	for (i = count - size; i < count; i++)
	{
		result = result + ((*(str + i) - '0') * multiplier);
		multiplier /= 10;
	}

	return (result * sign);
}
