#include "main.h"

unsigned int print_width(buffer_t *output, unsigned int printed,
		unsigned char flags, int wid);
unsigned int print_string_width(buffer_t *output,
		unsigned char flags, int wid, int prec, int size);
unsigned int print_neg_width(buffer_t *output, unsigned int printed,
		unsigned char flags, int wid);

/**
 * print_width - This func Stores leading spaces.
 * @output: A character array of a buffer_t struct.
 * @printed: Number of characters printed to output.
 * @flags: Flag modifiers.
 * @wid: width modifier
 * Return: Numb of bytes stored in the buffer.
 */

unsigned int print_width(buffer_t *output, unsigned int printed,
		unsigned char flags, int wid)
{
	unsigned int retr = 0;
	char width = ' ';

	if (NEG_FLAG == 0)
	{
		for (wid -= printed; wid > 0;)
		{
			retr += _memcpy(output, &width, 1);
		}
	}
	return (retr);
}

/**
 * print_string_width - This tores trailing spaces
 * @output:character array of buffer_t struct.
 * @flags: Flag modifiers.
 * @wid: A width modifier.
 * @prec: A precision modifier.
 * @size: The size of the string.
 * Return: The number of bytes stored to the buffer.
 */
unsigned int print_string_width(buffer_t *output,
		unsigned char flags, int wid, int prec, int size)
{
	unsigned int retr = 0;
	char width = ' ';

	if (NEG_FLAG == 0)
	{
		wid -= (prec == -1) ? size : prec;
		for (; wid > 0; wid--)
		{
			retr += _memcpy(output, &width, 1);
		}
	}
	return (retr);
}

/**
 * print_neg_width - This stores trailing.
 * @output: Character array of biffer_t struct.
 * @printed: Number of bytes already stored to output.
 * @flags: Flag modifiers.
 * @wid: width modifier.
 * Return: Number of bytes stored to the buffer.
 */

unsigned int print_neg_width(buffer_t *output, unsigned int printed,
		unsigned char flags, int wid)
{
	unsigned int retr = 0;
	char width = ' ';

	if (NEG_FLAG == 1)
	{
		for (wid -= printed; wid > 0; wid--)
		{
			retr += _memcpy(output, &width, 1);
		}
	}
	return (retr);
}

