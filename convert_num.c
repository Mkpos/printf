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
	long int dgt, cpy;
	unsigned int rtn = 0;
	unsigned int itr = 0;
	char pad;
	char space = ' ';
	char neg = '-';
	char plus = '+';

	if (len == LONG)
		dgt = va_arg(args, long int);
	else
		dgt = va_arg(args, int);
	if (len == SHORT)
		dgt = (short)dgt;

	if (SPACE_FLAG == 1 && dgt >= 0)
		rtn += _memcpy(output, &space, 1);

	if (prec <= 0 && NEG_FLAG == 0)
	{
		if (dgt == LONG_MIN)
			itr += 19;
		else
		{
			for (cpy = (dgt < 0) ? -dgt : dgt; cpy > 0; cpy /= 10)
				itr++;
		}
		itr += (dgt == 0) ? 1 : 0;
		itr += (dgt < 0) ? 1 : 0;
		itr += (PLUS_FLAG == 1 && dgt >= 0) ? 1 : 0;
		itr += (SPACE_FLAG == 1 && dgt >= 0) ? 1 : 0;

		if (ZERO_FLAG == 1 && PLUS_FLAG == 1 && dgt >= 0)
			rtn += _memcpy(output, &plus, 1);
		if (ZERO_FLAG == 1 && dgt < 0)
			rtn += _memcpy(output, &neg, 1);

		pad = (ZERO_FLAG == 1) ? '0' : ' ';
		for (wid -= itr; wid > 0; wid--)
			rtn += _memcpy(output, &pad, 1);
	}

	/* Print negative sign when zero flag is not active */
	if (ZERO_FLAG == 0 && dgt < 0)
		rtn += _memcpy(output, &neg, 1);
	/* Handle plus flag when zero flag is not active */
	if (ZERO_FLAG == 0 && (PLUS_FLAG == 1 && dgt >= 0))
		rtn += _memcpy(output, &plus, 1);

	if (!(dgt == 0 && prec == 0))
		rtn += convert_sbase(output, dgt, "0123456789",
				flags, 0, prec);

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
		dgt = va_arg(args, unsigned long int);
	else
		dgt = va_arg(args, unsigned int);
	if (len == SHORT)
		dgt = (unsigned short)dgt;

	if (HASH_FLAG == 1 && dgt != 0)
		rtn += _memcpy(output, &zero, 1);

	if (!(dgt == 0 && prec == 0))
		rtn += convert_ubase(output, dgt, "01234567",
				flags, wid, prec);

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
	unsigned int rtn = 0;

	if (len == LONG)
		dgt = va_arg(args, unsigned long int);
	else
		dgt = va_arg(args, unsigned int);
	if (len == SHORT)
		dgt = (unsigned short)dgt;

	if (!(dgt == 0 && prec == 0))
		rtn += convert_ubase(output, dgt, "0123456789",
				flags, wid, prec);

	rtn += print_neg_width(output, rtn, flags, wid);

	return (rtn);
}
