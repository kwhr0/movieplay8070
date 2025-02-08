#include "types.h"

void FileInit(void);
void FileOpen(u16 cluster, u32 len);
int FileGetChar(void);
void FileGetRGBs(u8 *buf, u16 len);
void FileSkip(u32 len);
u32 FileTell(void);
void DirOpen(u16 cluster);
char *DirRead(void);
