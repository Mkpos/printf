#include "main.h"

unsigned int convert_x(va_list args, buffer_t *output,
		unsigned char flags, int wid, int prec, unsigned char len);
unsigned int convert_X(va_list args, buffer_t *output,
		unsigned char flags, int wid, int prec, unsigned char len);


/**
 * convert_x - Converts an unsigned int arg to hex and stores it in a struct.
 * @args: A pointer to the argument to be converted
 * @flags: flag accepted
 * @wid: accepts width
 * @prec: accept precision
 * @len: accepts length
 * @output: A struct containing array
 *
 * Return: The number of bytes stored
 */
unsigned int convert_x(va_list args, buffer_t *output,
		unsigned char flags, int wid, int prec, unsigned char len)
{
	unsigned long int dgt;
	unsigned int rtn = 0;
	char *hexa = "0x";

	if (len == LONG)
		dgt = va_arg(args, unsigned long int);
	else
		dgt = va_arg(args, unsigned int);
	if (len == SHORT)
		dgt = (unsigned short)dgt;

	if (HASH_FLAG == 1 && dgt != 0)
		rtn += _memcpy(output, hexa, 2);

	if (!(dgt == 0 && prec == 0))
		rtn += convert_ubase(output, dgt, "0123456789abcdef",
				flags, wid, prec);

	rtn += print_neg_width(output, rtn, flags, wid);

	return (rtn);
}

/**
 * convert_X - Converts an unsigned int arg to hex and stores it in a struct.
 * @args: A pointer to the argument to be converted
 * @flags: Flags
 * @wid: width
 * @prec: precision
 * @len: length
 * @output: A buffer_t struct containing a character array.
 *
 * Return: The number of bytes stored
 */
unsigned int convert_X(va_list args, buffer_t *output,
		unsigned char flags, int wid, int prec, unsigned char len)
{
	unsigned long int dgt;
	unsigned int rtn = 0;
	char *hexa = "0X";

	if (len == LONG)
		dgt = va_arg(args, unsigned long);
	else
		dgt = va_arg(args, unsigned int);
	if (len == SHORT)
		dgt = (unsigned short)dgt;

	if (HASH_FLAG == 1 && dgt != 0)
		rtn += _memcpy(output, hexa, 2);

	if (!(dgt == 0 && prec == 0))
		rtn += convert_ubase(output, dgt, "0123456789ABCDEF",
				flags, wid, prec);

	rtn += print_neg_width(output, rtn, flags, wid);

	return (rtn);
}
