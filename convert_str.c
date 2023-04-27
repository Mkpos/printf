#include "main.h"

unsigned int convert_s(va_list args, buffer_t *output,
		unsigned char flags, int wid, int prec, unsigned char len);
unsigned int convert_S(va_list args, buffer_t *output,
		unsigned char flags, int wid, int prec, unsigned char len);
unsigned int convert_r(va_list args, buffer_t *output,
		unsigned char flags, int wid, int prec, unsigned char len);
unsigned int convert_R(va_list args, buffer_t *output,
		unsigned char flags, int wid, int prec, unsigned char len);

/**
 * convert_s - Converts an argument to a string and and pass into a struct
 * @args: A variable_list pointing to the argument to be converted to string
 * @flags: flag modifier
 * @wid: A width modifier
 * @prec: A precision modifier
 * @len: A length modifier
 * @output: A struct buffer that contains a character array.
 *
 * Return: The number of bytes stored
 */

unsigned int convert_s(va_list args, buffer_t *output,
		unsigned char flags, int wid, int prec, unsigned char len)
{
	char *string, *no = "(null)";
	int byte;
	unsigned int rtn = 0;

	(void)flags;
	(void)len;

	string = va_arg(args, char *);
	if (string == NULL)
		return (_memcpy(output, no, 6));

	for (byte = 0; *(string + byte);)
		byte++;

	rtn += print_string_width(output, flags, wid, prec, byte);

	prec = (prec == -1) ? byte : prec;
	while (*string != '\0' && prec > 0)
	{
		rtn += _memcpy(output, string, 1);
		prec--;
		string++;
	}

	rtn += print_neg_width(output, rtn, flags, wid);

	return (rtn);
}

/**
 * convert_S - Converts an arg to a string stores it in a struct.
 * @args: A pointer to the argunent passed
 * @flags: Flag
 * @wid: width
 * @prec: precision
 * @len: length
 * @output: A buffer_t struct containing a character array.
 *
 * Return: The number of bytes stored
 */

unsigned int convert_S(va_list args, buffer_t *output,
		unsigned char flags, int wid, int prec, unsigned char len)
{
	char *string, *no = "(null)", *hex = "\\x", zero = '0';
	int byte;
	int i;
	unsigned int rtn = 0;

	(void)len;
	string = va_arg(args, char *);
	if (string == NULL)
		return (_memcpy(output, no, 6));

	for (byte = 0; string[byte];)
		byte++;

	rtn += print_string_width(output, flags, wid, prec, byte);

	prec = (prec == -1) ? byte : prec;
	for (i = 0; *(string + i) != '\0' && i < prec; i++)
	{
		if (*(string + i) < 32 || *(string + i) >= 127)
		{
			rtn += _memcpy(output, hex, 2);
			if (*(string + i) < 16)
				rtn += _memcpy(output, &zero, 1);
			rtn += convert_ubase(output, *(string + i),
					     "0123456789ABCDEF", flags, 0, 0);
			continue;
		}
		rtn += _memcpy(output, (string + i), 1);
	}

	rtn += print_neg_width(output, rtn, flags, wid);

	return (rtn);
}

/**
 * convert_r - stores a reverse st{red in struct
 * @args: pointer to sfring to be reversed
 * @flags: Flag modifiers
 * @wid: A width modifie.
 * @prec: A precision modifier
 * @len: A length modifier
 * @output: A buffer_t struct containing a character array.
 *
 * Return: The number of bytes stored
 */
unsigned int convert_r(va_list args, buffer_t *output,
		unsigned char flags, int wid, int prec, unsigned char len)
{
	char *string, *no = "(null)";
	int byte, end, i;
	unsigned int rtn = 0;

	(void)flags;
	(void)len;

	string = va_arg(args, char *);
	if (string == NULL)
		return (_memcpy(output, no, 6));

	for (byte = 0; *(string + byte);)
		byte++;

	rtn += print_string_width(output, flags, wid, prec, byte);

	end = byte - 1;
	prec = (prec == -1) ? byte : prec;
	for (i = 0; end >= 0 && i < prec; i++)
	{
		rtn += _memcpy(output, (string + end), 1);
		end--;
	}

	rtn += print_neg_width(output, rtn, flags, wid);

	return (rtn);
}

/**
 * convert_R - Converts a string to ROT13 and stores it in a struct.
 * @args: A pointer to the string to be converted.
 * @flags: Flag modifiers
 * @wid: A width modifier
 * @prec: A precision modifier
 * @len: A lenth modifier
 * @output: A buffer_t struct containing array char
 *
 * Return: The number of bytes stored.
 */
unsigned int convert_R(va_list args, buffer_t *output,
		unsigned char flags, int wid, int prec, unsigned char len)
{
	char *alpha = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	char *rot13 = "nopqrstuvwxyzabcdefghijklmNOPQRSTUVWXYZABCDEFGHIJKLM";
	char *string, *no = "(null)";
	int i, j, byte;
	unsigned int rtn = 0;

	(void)flags;
	(void)len;

	string = va_arg(args, char *);
	if (string == NULL)
		return (_memcpy(output, no, 6));

	for (byte = 0; *(string + byte);)
		byte++;

	rtn += print_string_width(output, flags, wid, prec, byte);

	prec = (prec == -1) ? byte : prec;
	for (i = 0; *(string + i) != '\0' && i < prec; i++)
	{
		for (j = 0; j < 52; j++)
		{
			if (*(string + i) == *(alpha + j))
			{
				rtn += _memcpy(output, (rot13 + j), 1);
				break;
			}
		}
		if (j == 52)
			rtn += _memcpy(output, (string + i), 1);
	}

	rtn += print_neg_width(output, rtn, flags, wid);

	return (rtn);
}
