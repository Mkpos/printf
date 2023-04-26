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
	char *string, *null_pointer = "(null)";
	int size;
	unsigned int itr = 0;

	(void)flags;
	(void)len;

	string = va_arg(args, char *);
	if (string == NULL)
		return (_memcpy(output, null_pointer, 6));

	for (size = 0; *(string + size);)
		size++;

	itr += print_string_width(output, flags, wid, prec, size);

	prec = (prec == -1) ? size : prec;
	while (*string != '\0' && prec > 0)
	{
		itr += _memcpy(output, string, 1);
		prec--;
		string++;
	}

	itr += print_neg_width(output, itr, flags, wid);

	return (itr);
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
 *
 */
unsigned int convert_S(va_list args, buffer_t *output,
		unsigned char flags, int wid, int prec, unsigned char len)
{
	char *string, *null_pointer = "(null)", *hex = "\\x", zero = '0';
	int size, i;
	unsigned int ret = 0;

	(void)len;
	string = va_arg(args, char *);
	if (string == NULL)
		return (_memcpy(output, null_pointer, 6));

	for (size = 0; string[size];)
		size++;

	ret += print_string_width(output, flags, wid, prec, size);

	prec = (prec == -1) ? size : prec;
	for (i = 0; *(string + i) != '\0' && i < prec; i++)
	{
		if (*(string + i) < 32 || *(string + i) >= 127)
		{
			ret += _memcpy(output, hex, 2);
			if (*(string + i) < 16)
				ret += _memcpy(output, &zero, 1);
			ret += convert_ubase(output, *(string + i),
					     "0123456789ABCDEF", flags, 0, 0);
			continue;
		}
		ret += _memcpy(output, (string + i), 1);
	}

	ret += print_neg_width(output, ret, flags, wid);

	return (ret);
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
	char *str, *null = "(null)";
	int byte, end, a;
	unsigned int ret = 0;

	(void)flags;
	(void)len;

	str = va_arg(args, char *);
	if (str == NULL)
		return (_memcpy(output, null, 6));

	for (byte = 0; *(str + byte);)
		byte++;

	ret += print_string_width(output, flags, wid, prec, byte);

	end = byte - 1;
	prec = (prec == -1) ? byte : prec;
	for (a = 0; end >= 0 && a < prec; a++)
	{
		ret += _memcpy(output, (str + end), 1);
		end--;
	}

	ret += print_neg_width(output, ret, flags, wid);

	return (ret);
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
	char *ptr1 = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	char *ptr2 = "nopqrstuvwxyzabcdefghijklmNOPQRSTUVWXYZABCDEFGHIJKLM";
	char *str, *null = "(null)";
	int a, j, size;
	unsigned int itr = 0;

	(void)flags;
	(void)len;

	str = va_arg(args, char *);
	if (str == NULL)
	{
		return (_memcpy(output, null, 6));
	}

	for (size = 0; *(str + size);)
	{
		size++;
	}

	itr += print_string_width(output, flags, wid, prec, size);

	prec = (prec == -1) ? size : prec;
	for (a = 0; *(str + a) != '\0' && a < prec; a++)
	{
		for (j = 0; j < 52; j++)
		{
			if (*(str + a) == *(ptr1 + j))
			{
				itr += _memcpy(output, (ptr2 + j), 1);
				break;
			}
		}
		if (j == 52)
			itr += _memcpy(output, (str + a), 1);
	}

	itr += print_neg_width(output, itr, flags, wid);

	return (itr);
}
