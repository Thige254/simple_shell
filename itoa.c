#include "shell.h"
#include <stdio.h>
#include <stdlib.h> /* For dynamic memory allocation functions */

/**
 * itoa - converts an integer to a string
 *
 * @num: the integer to convert
 * Return: the string representation of the integer
 */
char *itoa(int num)
{

	char *str = malloc(12); /* Assuming a 32-bit integer; */
	sprintf(str, "%d", num);

	return (str);

}
