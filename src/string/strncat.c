#include <string.h>

char *strncat(char *restrict d, const char *restrict s, size_t n)
{
	__strscpy(d + strlen(d), s, n + 1);
	return d;
}
