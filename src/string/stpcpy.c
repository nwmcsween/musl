#include <string.h>
#include <stdint.h>

#define has_zero(x) ((x) - (0 ? (x) : -1) / 0xff & ~(x) & (0 ? (x) : -1) / 0xff * 0x80)

char *__stpcpy(char *restrict d, const char *restrict s)
{
#ifdef __GNUC__
	typedef size_t __attribute__((__may_alias__)) word;
	word *wd;
	const word *ws;

	if ((uintptr_t)d % sizeof(word) != (uintptr_t)s % sizeof(word)) goto bytewise;

	for (; (uintptr_t)s % sizeof(word) && (*d = *s); d++, s++);

	wd = (void *)d; ws = (const void *)s;
	for (; !has_zero(*ws); wd++, ws++) *wd = *ws;
	d = (void *)wd; s = (const void *)ws;

bytewise:
#endif
	for (; *d = *s; d++, s++);

	return d;
}

weak_alias(__stpcpy, stpcpy);
