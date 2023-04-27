#include "main.h"

unsigned int print_width(buffer_t *output, unsigned int printed,
		unsigned char flags, int wid);
unsigned int print_string_width(buffer_t *output,
		unsigned char flags, int wid, int prec, int size);
unsigned int print_neg_width(buffer_t *output, unsigned int printed,
		unsigned char flags, int wid);

/**
 * print_width - This function stores trailing spaces..
 * @output: A character array containing a buffer_t struct
 * @printed: The current number of char already printed to outpu.
 * @flags: This is a lag modifiers.
 * @wid: This is a width modifier.
 *
 * Return: Numb of bytes stored to the buffer.
 */
unsigned int print_width(buffer_t *output, unsigned int printed,
		unsigned char flags, int wid)
{
	unsigned int retr = 0;
	char wedth = ' ';

	if (NEG_FLAG == 0)
	{
		for (wid -= printed; wid > 0;)
		{
			retr += _memcpy(output, &wedth, 1);
		}
	}

	return (retr);
}

/**
 * print_string_width - Tbis function Stores leading spacer.
 * @output: A character array containing a buffer_t struct.
 * @flags: This is a flag modifiers.
 * @wid: This is a width modifier.
 * @prec: This is a precision modifier.
 * @size: Size of the str
 *
 * Return: number of bytes stored to the buffer.
 */
unsigned int print_string_width(buffer_t *output,
		unsigned char flags, int wid, int prec, int size)
{
	unsigned int retr = 0;
	char wedth = ' ';

	if (NEG_FLAG == 0)
	{
		wid -= (prec == -1) ? size : prec;
		for (; wid > 0; wid--)
		{
			retr += _memcpy(output, &wedth, 1);
		}
	}

	return (retr);
}

/**
 * print_neg_width - This function Stores leading spaces.
 * @output: A character array containing a pointer to buffer_t struct..
 * @printed: The number of bytes already stored to output.
 * @flags: This is a flag modifiers.
 * @wid: This is a width modifier.
 *
 * Return: The number of bytes stored to the buffer.
 */
unsigned int print_neg_width(buffer_t *output, unsigned int printed,
		unsigned char flags, int wid)
{
	unsigned int retr = 0;
	char wedth = ' ';

	if (NEG_FLAG == 1)
	{
		for (wid -= printed; wid > 0; wid--)
		{
			retr += _memcpy(output, &wedth, 1);
		}
	}

	return (retr);
}
