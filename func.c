#include "shell.h"
/**
 * _memcpy - copy memory from source to destination
 * @dest: destination
 * @src: source
 * @n: number of bytes
 */
void _memcpy(void *dest, const void *src, size_t n)
{
	char *d = dest;
	const char *s = src;
	size_t i;

	for (i = 0; i < n; i++)
		d[i] = s[i];
}
