#include <stddef.h>
#include <stdint.h>

#define has_zero(x) ((x) - (0 ? (x) : -1) / 0xff & ~(x) & (0 ? (x) : -1) / 0xff * 0x80)

size_t __strscpy(char *restrict d, const char *restrict s, size_t n)
{
	const char *const d0 = d;

	if (!n--) return 0;
#ifdef __GNUC__

        typedef size_t __attribute__((__may_alias__)) word;
        word *wd;
        const word *ws;

        if ((uintptr_t)d % sizeof(word)  != (uintptr_t)s % sizeof(word)
            || n < sizeof(word) * 2) goto bytewise;

	for (; (uintptr_t)s % sizeof(word)
	        && (*d = *s); d++, s++, n--);

	wd = (void *)d; ws = (const void *)s;
	for (; n >= sizeof(word) && !has_zero(*ws)
	     ; wd++, ws++, n -= sizeof(word)) *wd = *ws;
	d = (void *)wd; s = (const void *)ws;

bytewise:
#endif
	for (; n && (*d = *s); d++, s++, n--);

	*d = 0;

	return d - d0;
}
