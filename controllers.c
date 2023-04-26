#include "main.h"

/**
 * handle_flags - Matches flags with values that match
 * @flag: this is a pointer that point to a potential string of flags
 * @index: indexing
 *
 * Return: If character match return a corresponding value
 * else return - (0)
 */

unsigned char handle_flags(const char *flag, char *index)
{
	int var1 = 0, var2 = 0;
	unsigned char man = 0;
	flag_t flags[] = {
		{'+', PLUS},
		{' ', SPACE},
		{'#', HASH},
		{'0', ZERO},
		{'-', NEG},
		{0, 0}
	};

	while (flag[var1] != 0)
	{
		while (flags[var2].flag != 0)
		{
			if (flag[var1] == flags[var2].flag)
			{
				(*index)++;
				if (man == 0)
				{
					man = flags[var2].value;
				}
				else
				{
					man |= flags[var2].value;
				}
				break;
			}
			var2++;
		}
		if (flags[var2].value == 0)
		{
			break;
		}
		var1++;
		var2 = 0;
	}

	return (man);
}


/**
 * handle_length - This function matches length modifiers
 * @modifier: argument
 * @index: argument
 *
 * Return: If a lenth matched return its corresponding value.
 * else return 0
 */
unsigned char handle_length(const char *modifier, char *index)
{
	if (*modifier == 'h')
	{
		(*index)++;
		return (SHORT);
	}

	else if (*modifier == 'l')
	{
		(*index)++;
		return (LONG);
	}

	return (0);
}

/**
 * handle_width - This function matches a width modifier
 * @args: Argument passed
 * @modifier: modifier argument passed
 * @index: number of index
 *
 * Return: If a width modifier is matched return its value
 * else return 0
 */
int handle_width(va_list args, const char *modifier, char *index)
{
	int value = 0;

	while ((*modifier >= '0' && *modifier <= '9') || (*modifier == '*'))
	{
		(*index)++;

		if (*modifier == '*')
		{
			value = va_arg(args, int);
			if (value <= 0)
				return (0);
			return (value);
		}

		value *= 10;
		value += (*modifier - '0');
		modifier++;
	}

	return (value);
}

/**
 *handle_precision - This function matcges precesion with its value
 * @args: argument for var_list
 * @modifier: A pointer that points to a precision modifier
 * @index: An index counter.
 *
 * Return: If a precision modifier is matched return its value.
 * If the precision modifier is empty, zero, or negative return 0
 * else return -1.
 */
int handle_precision(va_list args, const char *modifier, char *index)
{
	int val = 0;

	if (*modifier != '.')
	{
		return (-1);
	}
	modifier++;
	(*index)++;
	if ((*modifier <= '0' || *modifier > '9') &&
	     *modifier != '*')
	{
		if (*modifier == '0')
		{
			(*index)++;
		}
		return (0);
	}
	while ((*modifier >= '0' && *modifier <= '9') ||
	       (*modifier == '*'))
	{
		(*index)++;

		if (*modifier == '*')
		{
			val = va_arg(args, int);
			if (val <= 0)
			{
				return (0);
			}
			return (val);
		}

		val *= 10;
		val += (*modifier - '0');
		modifier++;
	}
	return (val);
}

/**
 * handle_specifiers - This function matches a conversion specifier
 * @int: argument for int
 * @char: argument for char
 * @specifier: A pointer that points  to a potential conversion specifier.
 *
 * Return: If a conversion function matches witha pointer to the function
 *         else return NULL
 */

unsigned int (*handle_specifiers(const char *specifier))(va_list, buffer_t *,
		unsigned char, int, int, unsigned char)
{
	int var1 = 0;

	converter_t converters[] = {
		{'c', convert_c},
		{'s', convert_s},
		{'d', convert_di},
		{'i', convert_di},
		{'%', convert_percent},
		{'b', convert_b},
		{'u', convert_u},
		{'o', convert_o},
		{'x', convert_x},
		{'X', convert_X},
		{'S', convert_S},
		{'p', convert_p},
		{'r', convert_r},
		{'R', convert_R},
		{0, NULL}
	};

	while (converters[var1].func)
	{
		if (converters[var1].specifier == *specifier)
		{
			return (converters[var1].func);
		}
		var1++;
	}

	return (NULL);
}
