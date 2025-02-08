#include "types.h"

#define putd(v)			putv(v, 0, 0x88)
#define putu(v)			putv(v, 0, 0x08)
#define putX(v)			putv(v, 0, 0x0e)
#define putx(v)			putv(v, 0, 0x2e)
#define put0X(v)		putv(v, 0, 0x1e)
#define put0x(v)		putv(v, 0, 0x3e)
#define puto(v)			putv(v, 0, 0x06)
#define putb(v)			putv(v, 0, 0x00)
#define put0o(v)		putv(v, 0, 0x16)
#define put0b(v)		putv(v, 0, 0x10)

#define putdn(v, n)		putv(v, n, 0x88)
#define putun(v, n)		putv(v, n, 0x08)
#define putXn(v, n)		putv(v, n, 0x0e)
#define putxn(v, n)		putv(v, n, 0x2e)
#define put0Xn(v, n)	putv(v, n, 0x1e)
#define put0xn(v, n)	putv(v, n, 0x3e)
#define puton(v, n)		putv(v, n, 0x06)
#define putbn(v, n)		putv(v, n, 0x00)
#define put0on(v, n)	putv(v, n, 0x16)
#define put0bn(v, n)	putv(v, n, 0x10)

#define putc(c)			putchar(c)
#define lf				putchar('\n')

void putchar(int c);
void putv(u16 v, s16 n, u16 m);
void puts_n(const char *s);
void puts(const char *s);

