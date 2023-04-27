#include "main.h"

unsigned int convert_sbase(buffer_t *output, long int num, char *base,
		unsigned char flags, int wid, int prec);
unsigned int convert_ubase(buffer_t *output,
		unsigned long int num, char *base,
		unsigned char flags, int wid, int prec);

/**
 * convert_sbase - This function Converts a signed long.
 * @output: A character array containing a buffer_t struct.
 * @num: Argument.
 * @base: A pointer to a string.
 * @flags: The Flag modifiers.
 * @wid: Modifiers for width
 * @prec: Modifiers for precision.
 * Return: Numb of bytes stored to the buffer.
 */
unsigned int convert_sbase(buffer_t *output, long int num, char *base,
		unsigned char flags, int wid, int prec)
{
	int sz;
	char dt;
	char pd = '0';
	unsigned int retr = 1;

	for (sz = 0; *(base + sz);)
		sz++;

	if (num >= sz || num <= -sz)
		retr += convert_sbase(output, num / sz, base,
				flags, wid - 1, prec - 1);

	else
	{
		for (; prec > 1; prec--, wid--)
			retr += _memcpy(output, &pd, 1);

		if (NEG_FLAG == 0)
		{
			pd = (ZERO_FLAG == 1) ? '0' : ' ';
			for (; wid > 1; wid--)
				retr += _memcpy(output, &pd, 1);
		}
	}

	dt = base[(num < 0 ? -1 : 1) * (num % sz)];
	_memcpy(output, &dt, 1);

	return (retr);
}

/**
 * convert_ubase - This function Converts an unsigned long data type.
 * @output: A chaacter array containing a buffer_t struct.
 * @num: An unsigned long to be converted.
 * @base: This is a pointer to a string.
 * @flags: A Flag modifiers.
 * @wid: modifier for width.
 * @prec: precision modifier.
 * Return: Numb of bytes stored to the buffer.
 */
unsigned int convert_ubase(buffer_t *output, unsigned long int num, char *base,
		unsigned char flags, int wid, int prec)
{
	unsigned int sz;
	unsigned int retr = 1;
	char digit, pd = '0', *lead = "0x";

	for (sz = 0; *(base + sz);)
		sz++;

	if (num >= sz)
		retr += convert_ubase(output, num / sz, base,
				flags, wid - 1, prec - 1);

	else
	{
		if (((flags >> 5) & 1) == 1)
		{
			wid -= 2;
			prec -= 2;
		}
		for (; prec > 1; prec--, wid--)
			retr += _memcpy(output, &pd, 1);

		if (NEG_FLAG == 0)
		{
			pd = (ZERO_FLAG == 1) ? '0' : ' ';
			for (; wid > 1; wid--)
				retr += _memcpy(output, &pd, 1);
		}
		if (((flags >> 5) & 1) == 1)
			retr += _memcpy(output, lead, 2);
	}

	digit = base[(num % sz)];
	_memcpy(output, &digit, 1);

	return (retr);
}
