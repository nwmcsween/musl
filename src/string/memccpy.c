#include <string.h>
#include <stdint.h>

#define has_zero(x) ((x) - (0 ? (x) : -1) / 0xff & ~(x) & (0 ? (x) : -1) / 0xff * 0x80)

void *memccpy(void *restrict _d, const void *restrict _s, int c, size_t n)
{
	c = (unsigned char)c;
	unsigned char *d = _d;
	const unsigned char *s = _s;
#ifdef __GNUC__
	typedef size_t __attribute__((__may_alias__)) word;
	word *wd;
	const word *ws, wi = (word)-1 / 0xff * c;

        if ((uintptr_t)d % sizeof(word) != (uintptr_t)s % sizeof(word)
	    || n < sizeof(word) * 2) goto bytewise;

	for (; (uintptr_t)s % sizeof(word) && *s != c
	     ; d++, s++, n--) *d = *s;

	wd = (void *)d; ws = (const void *)s;
	for (;  n >= sizeof(word) && !has_zero(*ws ^ wi)
	     ; *wd++ = *ws++, n -= sizeof(word));
	d = (void *)wd; s = (const void *)ws;

bytewise:
#endif
	for (; n && *d != c; *d++ = *s++, n--);

	return n ? d + 1 : 0;
}
