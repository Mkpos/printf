#include "main.h"

unsigned int convert_c(va_list args, buffer_t *output,
		unsigned char flags, int wid, int prec, unsigned char len);
unsigned int convert_percent(va_list args, buffer_t *output,
		unsigned char flags, int wid, int prec, unsigned char len);
unsigned int convert_p(va_list args, buffer_t *output,
		unsigned char flags, int wid, int prec, unsigned char len);

/**
 * convert_c - Converts an arg to an unsigned char and stores it in a struct.
 * @args: A pointer to an argumnet to be converted.
 * @flags: Flag
 * @wid: width
 * @prec: A precision modifier
 * @len: length
 * @output: A struct containing arrays
 *
 * Return: The number of bytes stored
 */
unsigned int convert_c(va_list args, buffer_t *output,
		unsigned char flags, int wid, int prec, unsigned char len)
{
	char chr;
	unsigned int rtn = 0;

	(void)prec;
	(void)len;

	chr = va_arg(args, int);

	rtn += print_width(output, rtn, flags, wid);
	rtn += _memcpy(output, &chr, 1);
	rtn += print_neg_width(output, rtn, flags, wid);

	return (rtn);
}

/**
 * convert_percent - Stores a percent sign in struct.
 * @args: A pointer to the argument to be converted
 * @flags: Flag
 * @wid: width
 * @prec: precision
 * @len: length
 * @output: A struct containing arrays
 *
 * Return: 1 always
 */

unsigned int convert_percent(va_list args, buffer_t *output,
		unsigned char flags, int wid, int prec, unsigned char len)
{
	char percentage = '%';
	unsigned int rtn = 0;

	(void)args;
	(void)prec;
	(void)len;

	rtn += print_width(output, rtn, flags, wid);
	rtn += _memcpy(output, &percentage, 1);
	rtn += print_neg_width(output, rtn, flags, wid);

	return (rtn);
}

/**
 * convert_p - Converts the address of an arg to hex and stores in a struct.
 * @args: A pointer to the argument to be converted
 * @flags: Flag
 * @wid: widtg
 * @prec: precision
 * @len: length
 * @output: A struct containing array
 *
 * Return: The number of bytes stored
 */

unsigned int convert_p(va_list args, buffer_t *output,
		unsigned char flags, int wid, int prec, unsigned char len)
{
	char *no = "(nil)";
	unsigned long int address;
	unsigned int rtn = 0;

	(void)len;

	address = va_arg(args, unsigned long int);
	if (address == '\0')
		return (_memcpy(output, no, 5));

	flags |= 32;
	rtn += convert_ubase(output, address, "0123456789abcdef",
			flags, wid, prec);
	rtn += print_neg_width(output, rtn, flags, wid);

	return (rtn);
}
