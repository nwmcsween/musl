#include <string.h>
#include <stdint.h>

int memcmp(const void *_l, const void *_r, size_t n)
{
	const unsigned char *l = _l, *r = _r;
#ifdef __GNUC__
	typedef size_t __attribute__((__may_alias__)) word;
	const word *wl, *wr;

	if ((uintptr_t)l % sizeof(word) != (uintptr_t)r % sizeof(word)
	    || n < sizeof(word) * 2) goto bytewise;

	for (; (uintptr_t)l % sizeof(word) && *l == *r; l++, r++, n--);

	wl = (const void *)l; wr = (const void *)r;
	for (; n >= sizeof(word) && *wl == *wr
	     ; wl++, wr++, n -= sizeof(word));
	l = (const void *)wl; r = (const void *)wr;

bytewise:
#endif
	for (; n && *l == *r; l++, r++, n--);

	return n ? *l - *r : 0;
}
