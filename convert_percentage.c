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
	char car;
	unsigned int ret = 0;

	(void)prec;
	(void)len;

	car = va_arg(args, int);

	ret += print_width(output, ret, flags, wid);
	ret += _memcpy(output, &car, 1);
	ret += print_neg_width(output, ret, flags, wid);

	return (ret);
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
	unsigned int ret = 0;

	(void)args;
	(void)prec;
	(void)len;

	ret += print_width(output, ret, flags, wid);
	ret += _memcpy(output, &percentage, 1);
	ret += print_neg_width(output, ret, flags, wid);

	return (ret);
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
	char *null = "(nil)";
	unsigned long int add;
	unsigned int rtn = 0;

	(void)len;

	add = va_arg(args, unsigned long int);
	if (add == '\0')
	{
		return (_memcpy(output, null, 5));
	}
	flags |= 32;
	rtn += convert_ubase(output, add, "0123456789abcdef",
			flags, wid, prec);
	rtn += print_neg_width(output, rtn, flags, wid);

	return (rtn);
}
