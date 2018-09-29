#include <string.h>
#include <stdint.h>

#define has_zero(x) ((x) - (0 ? (x) : -1) / 0xff & ~(x) & (0 ? (x) : -1) / 0xff * 0x80)

int strncmp(const char *_l, const char *_r, size_t n)
{
	const unsigned char *l = (const void *)_l, *r = (const void *)_r;

	if (!n--) return 0;

#ifdef __GNUC__
	typedef size_t __attribute__((__may_alias__)) word;
	const word *wl, *wr;

        if ((uintptr_t)l % sizeof(word) != (uintptr_t)r % sizeof(word)
             || n < sizeof(word) * 2) goto bytewise;

	for (; (uintptr_t)l & sizeof(word) - 1 && *l && *l == *r
	     ; l++, r++, n--);

	wl = (const void *)l; wr = (const void *)r;
	for (; n >= sizeof(word) && !has_zero(*wl) && *wl == *wr
	     ; wl++, wr++, n -= sizeof(word));
	l = (const void *)wl; r = (const void *)wr;

bytewise:
#endif
	for (; n && *l && *l == *r; l++, r++, n--);

	return *l - *r;
}
