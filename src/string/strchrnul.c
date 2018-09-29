#include <string.h>
#include <stdint.h>

#define has_zero(x) ((x) - (0 ? (x) : -1) / 0xff & ~(x) & (0 ? (x) : -1) / 0xff * 0x80)

char *__strchrnul(const char *s, int c)
{
	c = (unsigned char)c;

	if (!c) return (char *)s + strlen((char *)s);

#ifdef __GNUC__
	typedef size_t __attribute__((__may_alias__)) word;
	const word *ws,  wc = (word)-1 / 0xff * c;

	for (; (uintptr_t)s % sizeof(word) && *s && *s != c; s++);

	ws = (const void *)s;
	for (; !has_zero(*ws) && !has_zero(*ws ^ wc); ws++);
	s = (const void *)ws;
#endif
	for (; *s && *s != c; s++);

	return (char *)s;
}

weak_alias(__strchrnul, strchrnul);
