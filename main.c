#include "base.h"
#include "file.h"

#define SOUND_ENABLE	0
#define VRAM			(u8 *)0x8000
#define ENTRY_N		32

typedef struct {
	u16 cluster;
	u32 len;
} Entry;

static Entry entry[ENTRY_N];
static int entryN;

static u32 get4() {
	u32 r;
	u16 i;
	for (i = 0; i < 4; i++) {
		s16 c = FileGetChar();
		if (c == -1) return 0;
		((u8 *)&r)[i] = c;
	}
	return r;
}

static u32 avi_prepare() {
	if (get4() != 0x46464952/*RIFF*/) return 0;
	get4();
	if (get4() != 0x20495641/*AVI */) return 0;
	while (1) {
		u32 type = get4(), len = get4();
		if (type == 0x5453494c/*LIST*/) {
			len -= 4;
			if (get4() == 0x69766f6d/*movi*/) return FileTell() + len;
		}
		FileSkip(len);
	}
}

static int play() {
	u32 end;
	u8 *dp;
	int key = 0;
	for (end = avi_prepare(); FileTell() < end && !(key = keydown());) {
		u32 type = get4(), len = get4();
		switch (((u8 *)&type)[2]) {
		case 'd':
			if (!len) break;
#if !SOUND_ENABLE
			waitVSync(2);
#endif
			FileGetRGBs(VRAM, len);
			break;
#if SOUND_ENABLE
		case 'w':
			if (SOUNDFILL) idle();
			while (len) {
				SOUND0 = FileGetChar();
				SOUND1 = FileGetChar();
				len -= 2;
			}
			break;
#endif
		default:
			FileSkip(len);
			break;
		}
	}
	return key ? key : KEY_RIGHT;
}

static int cmp(const char *s1, const char *s2, int n) {
	int i;
	for (i = 0; i < n && s1[i] == s2[i]; i++)
		;
	return i < n;
}

int main(void) {
	int i, t;
	char *buf;
	u32 len;
	FileInit();
	DirOpen(0);
	while ((buf = DirRead()) && cmp(buf, "MOVIE      ", 11))
		;
	if (!buf) return 1;
	DirOpen(*(u16 *)&buf[26]);
	while (buf = DirRead()) {
		if (entryN >= ENTRY_N) break;
		if (!cmp(buf + 8, "AVI", 3)) {
			Entry *e = &entry[entryN++];
			e->cluster = *(u16 *)&buf[26];
			e->len = *(u32 *)&buf[28];
		}
	}
	for (i = 0; i < entryN;) {
		Entry *e = &entry[i];
		FileOpen(e->cluster, e->len);
		switch (play()) {
			case KEY_RIGHT: if (++i >= entryN) i = 0; break;
			case KEY_LEFT: if (--i < 0) i = entryN - 1; break;
		}
	}
	return 0;
}
