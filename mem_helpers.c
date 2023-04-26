#include "main.h"

unsigned int _memcpy(buffer_t *output, const char *src, unsigned int n);
void free_buffer(buffer_t *output);
buffer_t *init_buffer(void);

/**
 * _memcpy - This func Copies num of bytes from mem area source to the buffer
 * @output: This is a buffer_t struct.
 * @src: A pointer to that point to the  memory area to be copied
 * @n: The number of bytes to be copied.
 * Return: The number of bytes copied.
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
 * free_buffer - This function will free buffer_t struct.
 * @output: This is the buffer_t struct to be freed
 */
void free_buffer(buffer_t *output)
{
	free(output->start);
	free(output);
}

/**
 * init_buffer - Will Initialize  a variable of struct type buffer_t.
 * Return: A pointer to the initialized buffer_t.
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