#include <string.h>
#include <stdint.h>

#define has_zero(x) ((x) - (0 ? (x) : -1) / 0xff & ~(x) & (0 ? (x) : -1) / 0xff * 0x80)

size_t strlen(const char *s)
{
	const char *const s0 = s;
#ifdef __GNUC__
	typedef size_t __attribute__((__may_alias__)) word;
	const word *ws;

	for (; (uintptr_t)s & sizeof(word) - 1 && *s; s++);

	ws = (const void *)s;
	for (; !has_zero(*ws); ws++);
	s = (const void *)ws;
#endif
	for (; *s; s++);

	return s - s0;
}
