#ifndef _TYPES_H_
#define _TYPES_H_

typedef signed char s8;
typedef signed short s16;
typedef signed long s32;
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;

// input

#define STREAM		(*(u8 *)0xfe00)
#define KEYBOARD	(*(u8 *)0xfe01)
#define SOUNDFILL	(*(u8 *)0xfe02)

#define KEY_RIGHT	28
#define KEY_LEFT	29

// output

#define SECTOR0		(*(u8 *)0xfe00)
#define SECTOR1		(*(u8 *)0xfe01)
#define SECTOR2		(*(u8 *)0xfe02)
#define SOUND0		(*(u8 *)0xfe04)
#define SOUND1		(*(u8 *)0xfe05)

#endif
