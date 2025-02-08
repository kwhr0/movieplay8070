#include "base.h"

void idle(void);

u8 frameCount;
extern u8 interruptCount, keyTarget, keyWait;

// format of "m"
// bit7    signed
// bit5    lower case
// bit4    zero prefixed
// bit3..0 radix-2
void putv(u16 v, s16 n, u16 m) {
	u8 c[17];
	s16 i = 0;
	u16 f, r = 2 + (m & 0xf), a = 7 + (m & 0x20), p = 0x20 + (m & 0x10);
	if (f = m & 0x80 && v & 0x8000) v = -v;
	do { // avoid fcc bug (not use '%')
		u16 d = v / r, t = v - d * r + '0';
		if (t > '9') t += a;
		c[i++] = t;
		v = d;
	} while (v);
	if (f) c[i++] = '-';
	if (n > 0) while (n-- > i) putchar(p);
	else n += i;
	do putchar(c[--i]);
	while (i);
	if (n < 0) while (n++) putchar(' ');
}

void puts_n(const char *s) {
	while (*s) putchar(*s++);
}

void puts(const char *s) {
	puts_n(s);
	putchar('\n');
}

int keydown(void) {
	static int lastKey;
	int c = KEYBOARD;
	if (c) {
		if (c != lastKey) {
			di();
			keyTarget = interruptCount + 40;
			keyWait = 1;
			ei();
		}
		else if (!keyWait) {
			di();
			keyTarget = interruptCount + 8;
			keyWait = 1;
			ei();
		}
		else return 0;
	}
	lastKey = c;
	return c;
}

u8 waitVSync(u8 frames) {
	u8 dif = (u8)interruptCount - frameCount;
	u8 f, t = frameCount + frames;
	if (t >= frameCount)
		while ((f = interruptCount) >= frameCount && f < t)
			idle();
	else
		while ((f = interruptCount) >= frameCount || f < t)
			idle();
	frameCount = f;
	return dif;
}

