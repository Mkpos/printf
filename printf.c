#include "main.h"

void cleanup(va_list args, buffer_t *output);
int mk_printf(const char *format, va_list args, buffer_t *output);
int _printf(const char *format, ...);

/**
 * cleanup - A function thst Peforms cleanup operations for _printf.
 * @args: This is a va_list of arguments provided to _printf.
 * @output: Represent A buffer_t struct.
 */

void cleanup(va_list args, buffer_t *output)
{
	va_end(args);
	write(1, output->start, output->len);
	free_buffer(output);
}

/**
 * mk_printf - This function Reads through the formated string for _printf.
 * @format: Character string to print - may contain directives.
 * @output: buffer_t struct containing a buffer.
 * @args: va_list of arguments.
 *
 * Return: numb of chars stored to output
 */

int mk_printf(const char *format, va_list args, buffer_t *output)
{
	int zu = 0;
	int wid;
	int prec;
	int man = 0;
	char tp;
	unsigned char flags, len;
	unsigned int (*f)(va_list, buffer_t *,
			unsigned char, int, int, unsigned char);

	while (*(format + zu))
	{
		len = 0;
		if (*(format + zu) == '%')
		{
			tp = 0;
			flags = handle_flags(format + zu + 1, &tp);
			wid = handle_width(args, format + zu + tp + 1, &tp);
			prec = handle_precision(args, format + zu + tp + 1,
					&tp);
			len = handle_length(format + zu + tp + 1, &tp);
			f = handle_specifiers(format + zu + tp + 1);
			if (f != NULL)
			{
				zu += tp + 1;
				man += f(args, output, flags, wid, prec, len);
				continue;
			}
			else if (*(format + zu + tp + 1) == '\0')
			{
				man = -1;
				break;
			}
		}
		man += _memcpy(output, (format + zu), 1);
		zu += (len != 0) ? 1 : 0;
	}

	cleanup(args, output);
	return (man);
}

/**
 * _printf - Standard func that output  a formatted string
 * @format: Char str to print.
 *
 * Return: Number of chars printed.
 */

int _printf(const char *format, ...)
{
	buffer_t *output;
	va_list args;
	int man;

	if (format == NULL)
	{
		return (-1);
	}
	output = init_buffer();
	if (output == NULL)
	{
		return (-1);
	}

	va_start(args, format);

	man = mk_printf(format, args, output);

	return (man);
}
