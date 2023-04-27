#include "main.h"

void cleanup(va_list args, buffer_t *output);
int run_printf(const char *format, va_list args, buffer_t *output);
int _printf(const char *format, ...);

/**
 * cleanup - function Peforms cleanup acrivities for _printf.
 * @args: Argument
 * @output: A buffer_t struct.
 */
void cleanup(va_list args, buffer_t *output)
{
	va_end(args);
	write(1, output->start, output->len);
	free_buffer(output);
}

/**
 * run_printf - Is a function that Reads through the fmt string for _printf.
 * @format: The char string to print.
 * @output: buffer_t struct containing a buffer.
 * @args: arguments.
 *
 * Return: The number of characters stored to output.
 */
int run_printf(const char *format, va_list args, buffer_t *output)
{
	int ab;
	int wd;
	int prec;
	int retr = 0;
	char tmp;
	unsigned char flags, len;
	unsigned int (*f)(va_list, buffer_t *,
			unsigned char, int, int, unsigned char);

	for (ab = 0; *(format + ab); ab++)
	{
		len = 0;
		if (*(format + ab) == '%')
		{
			tmp = 0;
			flags = handle_flags(format + ab + 1, &tmp);
			wd = handle_width(args, format + ab + tmp + 1, &tmp);
			prec = handle_precision(args, format + ab + tmp + 1,
					&tmp);
			len = handle_length(format + ab + tmp + 1, &tmp);

			f = handle_specifiers(format + ab + tmp + 1);
			if (f != NULL)
			{
				ab += tmp + 1;
				retr += f(args, output, flags, wd, prec, len);
				continue;
			}
			else if (*(format + ab + tmp + 1) == '\0')
			{
				retr = -1;
				break;
			}
		}
		retr += _memcpy(output, (format + ab), 1);
		ab += (len != 0) ? 1 : 0;
	}
	cleanup(args, output);
	return (retr);
}

/**
 * _printf - Outputs a formatted string.
 * @format: Char str to printed.
 *
 * Return: number of char printed.
 */
int _printf(const char *format, ...)
{
	buffer_t *output;
	va_list args;
	int retr;

	if (format == NULL)
		return (-1);
	output = init_buffer();
	if (output == NULL)
		return (-1);

	va_start(args, format);

	retr = run_printf(format, args, output);

	return (retr);
}
