#include <string.h>

char *__stpncpy(char *restrict d, const char *restrict s, size_t n)
{
	if (!n) return d;

	size_t r = __strscpy(d, s, n) + 1;

	/* remove nul termination... */
	if (s[r - 1]) d[r - 1] = s[r - 1];
	else memset(d + r, 0, n - r);

	return d + r;
}

weak_alias(__stpncpy, stpncpy);
