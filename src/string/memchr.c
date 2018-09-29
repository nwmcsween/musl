#include <string.h>
#include <stdint.h>

#define has_zero(x) ((x) - (0 ? (x) : -1) / 0xff & ~(x) & (0 ? (x) : -1) / 0xff * 0x80)

void *memchr(const void *_s, int c, size_t n)
{
	c = (unsigned char)c;
	const unsigned char *s = _s;
#ifdef __GNUC__
	typedef size_t __attribute__((__may_alias__)) word;
	const word *ws, wc = (word)-1 / 0xff * c;

	if (n < sizeof(word) * 2) goto bytewise;

	for (; (uintptr_t)s % sizeof(word) && *s != c; s++, n--);

	ws = (const void *)s;
	for (; n >= sizeof(word) && !has_zero(*ws ^ wc)
	     ; ws++, n -= sizeof(word));
	s = (const void *)ws;

bytewise:
#endif
	for (; n && *s != c; s++, n--);

	return n ? (void *)s : 0;
}
