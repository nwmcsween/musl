#define _BSD_SOURCE
#include <string.h>

size_t strlcpy(char *d, const char *s, size_t n)
{
	const size_t r = __strscpy(d, s, n);

	return r + strlen(s + r);
}
