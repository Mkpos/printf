#include "main.h"

unsigned int _memcpy(buffer_t *output, const char *src, unsigned int n);
void free_buffer(buffer_t *output);
buffer_t *init_buffer(void);

/**
 * _memcpy - This functiin Copies (n) bytes from memory area sour ce.
 * @output: A buffer_t struct.
 * @src: pointer to  memory area to copy.
 * @n: This is the number of bytes to be copied.
 * Return: The numb of bytes copied
 */
unsigned int _memcpy(buffer_t *output, const char *src, unsigned int n)
{
	unsigned int idx;

	for (idx = 0; idx < n; idx++)
	{
		*(output->buffer) = *(src + idx);
		(output->len)++;

		if (output->len == 1024)
		{
			write(1, output->start, output->len);
			output->buffer = output->start;
			output->len = 0;
		}

		else
		{
			(output->buffer)++;
		}
	}

	return (n);
}

/**
 * free_buffer - This function frees a buffer_t struct.
 * @output: buffer_t struct.
 */
void free_buffer(buffer_t *output)
{
	free(output->start);
	free(output);
}

/**
 * init_buffer - This is a function that Initializes a var(buffer_t).
 *
 * Return: An initialized pointer to buffer_t.
 */
buffer_t *init_buffer(void)
{
	buffer_t *output;

	output = malloc(sizeof(buffer_t));
	if (output == NULL)
	{
		return (NULL);
	}

	output->buffer = malloc(sizeof(char) * 1024);
	if (output->buffer == NULL)
	{
		free(output);
		return (NULL);
	}

	output->start = output->buffer;
	output->len = 0;

	return (output);
}
