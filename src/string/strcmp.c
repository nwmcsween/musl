#include <string.h>
#include <stdint.h>

#define has_zero(x) ((x) - (0 ? (x) : -1) / 0xff & ~(x) & (0 ? (x) : -1) / 0xff * 0x80)

int strcmp(const char *_l, const char *_r)
{
	const unsigned char *l = (const void *)_l, *r = (const void *)_r;
#ifdef __GNUC__
	typedef size_t __attribute__((__may_alias__)) word;
	const word *wl, *wr;

	if ((uintptr_t)l % sizeof(word) != (uintptr_t)r % sizeof(word)) goto bytewise;

	for (; (uintptr_t)l & sizeof(word) - 1 && *l && *l == *r; l++, r++);

	wl = (const void *)l; wr = (const void *)r;
	for (; !has_zero(*wl) && *wl == *wr; wl++, wr++);
	l = (const void *)wl; r = (const void *)wr;

bytewise:
#endif
	for (; *l && *l == *r; l++, r++);

	return *l - *r;
}
