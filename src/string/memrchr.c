#include <string.h>
#include <stdint.h>

#define has_zero(x) ((x) - (0 ? (x) : -1) / 0xff & ~(x) & (0 ? (x) : -1) / 0xff * 0x80)

void *__memrchr(const void *_s, int c, size_t n)
{
	c = (unsigned char )c;
	const unsigned char *s = _s;
#ifdef __GNUC__
	typedef size_t __attribute__((__may_alias__)) word;
	const word wi = (word)-1 / 0xff * c;

	if (n < sizeof(word) * 2) goto bytewise;

	for (; (uintptr_t)(s + n) & sizeof(word) - 1 && s[n - 1] != c; n--);

	for (; n >= sizeof(word) &&
	       !has_zero(*(word *)(s + n - sizeof(word)) ^ wi)
	     ; n -= sizeof(word));

bytewise:
#endif
	for (; n && s[n - 1] != c; n--);

	return n ? (void *)(s + n - 1) : 0;
}

weak_alias(__memrchr, memrchr);
