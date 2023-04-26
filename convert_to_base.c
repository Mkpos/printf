#include "main.h"

unsigned int convert_sbase(buffer_t *output, long int num, char *base,
		unsigned char flags, int wid, int prec);
unsigned int convert_ubase(buffer_t *output,
		unsigned long int num, char *base,
		unsigned char flags, int wid, int prec);

/**
 * convert_sbase - A function that Converts a signed long to an inputted base.
 * @output: A char of an array in a buffer_t struct .
 * @num: signed long type to be converted.
 * @base: This is a pointer to a string.
 * @flags: Modifiers for flag.
 * @wid: width modifiers
 * @prec: Modifier for precision.
 *
 * Return: Num of bytes stored to the buffer.
 */
unsigned int convert_sbase(buffer_t *output, long int num, char *base,
		unsigned char flags, int wid, int prec)
{
	int si;
	char dt;
	char pd = '0';
	unsigned int retr = 1;

	for (si = 0; *(base + si);)
	{
		si++;
	}

	if (num >= si || num <= -si)
	{
		retr += convert_sbase(output, num / si, base,
				flags, wid - 1, prec - 1);
	}
	else
	{
		for (; prec > 1; prec--, wid--)
		{
			retr += _memcpy(output, &pd, 1);
		}

		if (NEG_FLAG == 0)
		{
			pd = (ZERO_FLAG == 1) ? '0' : ' ';
			for (; wid > 1; wid--)
			{
				retr += _memcpy(output, &pd, 1);
			}
		}
	}

	dt = base[(num < 0 ? -1 : 1) * (num % si)];
	_memcpy(output, &dt, 1);

	return (retr);
}

/**
 * convert_ubase - It Converts an unsigned long to an inputted base.
 * @output: This is a buffer_t struct
 * @num: unsigned long to be changed.
 * @base: This is a pointer to a string.
 * @flags: Flag modifiers.
 * @wid: This is width modifier.
 * @prec: Modifier for precision
 *
 * Return: only number of bytes stored to the buffer.
 */
unsigned int convert_ubase(buffer_t *output, unsigned long int num, char *base,
		unsigned char flags, int wid, int prec)
{
	unsigned int si;
	unsigned int retr = 1;
	char dt, pd = '0', *lead = "0x";

	for (si = 0; *(base + si);)
	{
		si++;
	}
	if (num >= si)
	{
		retr += convert_ubase(output, num / si, base,
				flags, wid - 1, prec - 1);
	}
	else
	{
		if (((flags >> 5) & 1) == 1)
		{
			wid -= 2;
			prec -= 2;
		}
		for (; prec > 1; prec--, wid--)
		{
			retr += _memcpy(output, &pd, 1);
		}
		if (NEG_FLAG == 0)
		{
			pd = (ZERO_FLAG == 1) ? '0' : ' ';
			for (; wid > 1; wid--)
			{
				retr += _memcpy(output, &pd, 1);
			}
		}
		if (((flags >> 5) & 1) == 1)
		{
			retr += _memcpy(output, lead, 2);
		}
	}
	dt = base[(num % si)];
	_memcpy(output, &dt, 1);
	return (retr);
}
