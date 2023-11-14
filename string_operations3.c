#include "shell.h"

/**
 * reverse_string - Reverses a string.
 * @input_string: Input string.
 * Return: No return.
 */
void reverse_string(char *input_string)
{
	int length = 0, i, j;
	char *string_ptr, temp;

	while (length >= 0)
	{
		if (input_string[length] == '\0')
			break;
		length++;
	}
	string_ptr = input_string;

	for (i = 0; i < (length - 1); i++)
	{
		for (j = i + 1; j > 0; j--)
		{
			temp = *(string_ptr + j);
			*(string_ptr + j) = *(string_ptr + (j - 1));
			*(string_ptr + (j - 1)) = temp;
		}
	}
}
