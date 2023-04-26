#include "main.h"

unsigned int convert_di(va_list args, buffer_t *output,
		unsigned char flags, int wid, int prec, unsigned char len);
unsigned int convert_b(va_list args, buffer_t *output,
		unsigned char flags, int wid, int prec, unsigned char len);
unsigned int convert_u(va_list args, buffer_t *output,
		unsigned char flags, int wid, int prec, unsigned char len);
unsigned int convert_o(va_list args, buffer_t *output,
		unsigned char flags, int wid, int prec, unsigned char len);

/**
 * convert_di - Converts an argument to a signed int and stores in a struct.
 * @args: A pointer to the argument to be converted
 * @flags: Flags
 * @wid: width
 * @prec: precision
 * @len: length
 * @output: A buffer_t struct containing array
 *
 * Return: The number of bytes stored
 */

unsigned int convert_di(va_list args, buffer_t *output,
		unsigned char flags, int wid, int prec, unsigned char len)
{
	long int dst, yank;
	unsigned int rtn = 0;
	unsigned int count = 0;
	char pad;
	char gap = ' ';
	char minus = '-';
	char plus = '+';

	if (len == LONG)
	{
		dst = va_arg(args, long int);
	}
	else
	{
		dst = va_arg(args, int);
	}
	if (len == SHORT)
	{
		dst = (short)dst;
	}
	/* Handle gap flag */
	if (SPACE_FLAG == 1 && dst >= 0)
	{
		rtn += _memcpy(output, &gap, 1);
	}
	if (prec <= 0 && NEG_FLAG == 0)
	{
		if (dst == LONG_MIN)
		{
			count += 19;
		}
		else
		{
			for (yank = (dst < 0) ? -dst : dst; yank > 0; yank /= 10)
				count++;
		}
		count += (dst == 0) ? 1 : 0;
		count += (dst < 0) ? 1 : 0;
		count += (PLUS_FLAG == 1 && dst >= 0) ? 1 : 0;
		count += (SPACE_FLAG == 1 && dst >= 0) ? 1 : 0;

		if (ZERO_FLAG == 1 && PLUS_FLAG == 1 && dst >= 0)
		{
			rtn += _memcpy(output, &plus, 1);
		}
		/*when flag is active, this block prints a negative sign*/
		if (ZERO_FLAG == 1 && dst < 0)
		{
			rtn += _memcpy(output, &minus, 1);
		}
		pad = (ZERO_FLAG == 1) ? '0' : ' ';
		for (wid -= count; wid > 0; wid--)
		{
			rtn += _memcpy(output, &pad, 1);
		}
	}

	/* when zero flag isnt on, this block prints a negative sign*/
	if (ZERO_FLAG == 0 && dst < 0)
	{
		rtn += _memcpy(output, &minus, 1);
	}
	/* this helps to take care of + flag */
	if (ZERO_FLAG == 0 && (PLUS_FLAG == 1 && dst >= 0))
	{
		rtn += _memcpy(output, &plus, 1);
	}
	if (!(dst == 0 && prec == 0))
	{
		rtn += convert_sbase(output, dst, "0123456789",
				flags, 0, prec);
	}
	rtn += print_neg_width(output, rtn, flags, wid);

	return (rtn);
}

/**
 * convert_b - Converts an unsigned int argument to base 2and stores it in a struct.
 * @args: pointer to argument to be converted
 * @flags: Flag
 * @wid: width
 * @prec: precision modifier
 * @len: A length modifier.
 * @output: A buffer_t struct containing a character array.
 *
 * Return: The number of bytes stored to the buffer.
 */
unsigned int convert_b(va_list args, buffer_t *output,
		unsigned char flags, int wid, int prec, unsigned char len)
{
	unsigned int dgt;

	dgt = va_arg(args, unsigned int);

	(void)len;

	return (convert_ubase(output, dgt, "01", flags, wid, prec));
}

/**
 * convert_o - Converts an unsigned int to base 8stores it in a struct.
 * @args: A pointer tontge argument to be converted
 * @flags: Flag modifiers
 * @wid: A width modifier
 * @prec: A precision modifier
 * @len: A length modifier
 * @output: A buffer_t struct containing arrays
 *
 * Return: The number of bytes stored to the buffer.
 */
unsigned int convert_o(va_list args, buffer_t *output,
		unsigned char flags, int wid, int prec, unsigned char len)
{
	unsigned long int dgt;
	unsigned int rtn = 0;
	char zero = '0';

	if (len == LONG)
	{
		dgt = va_arg(args, unsigned long int);
	}
	else
	{
		dgt = va_arg(args, unsigned int);
	}
	if (len == SHORT)
	{
		dgt = (unsigned short)dgt;
	}
	if (HASH_FLAG == 1 && dgt != 0)
	{
		rtn += _memcpy(output, &zero, 1);
	}
	if (!(dgt == 0 && prec == 0))
	{
		rtn += convert_ubase(output, dgt, "01234567",
				flags, wid, prec);
	}

	rtn += print_neg_width(output, rtn, flags, wid);

	return (rtn);
}

/**
 * convert_u - Converts an unsigned int argument to base 10 and stores it in a struct
 * @args: A pointer to the argument to be converted
 * @flags: Flags
 * @wid: width
 * @prec: precision
 * @len: length
 * @output: A struct containing array
 *
 * Return: The number of bytes stored
 */
unsigned int convert_u(va_list args, buffer_t *output,
		unsigned char flags, int wid, int prec, unsigned char len)
{
	unsigned long int dgt;
	unsigned int ret = 0;

	if (len == LONG)
	{
		dgt = va_arg(args, unsigned long int);
	}
	else
	{
		dgt = va_arg(args, unsigned int);
	}
	if (len == SHORT)
	{
		dgt = (unsigned short)dgt;
	}
	if (!(dgt == 0 && prec == 0))
	{
		ret += convert_ubase(output, dgt, "0123456789",
				flags, wid, prec);
	}
	ret += print_neg_width(output, ret, flags, wid);

	return (ret);
}
