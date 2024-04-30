#pragma once
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#define COMPLETE		0
#define IMCOMPLETE		-1
#define ABNORMAL		1

#define BUFSIZE			1024
#define DebugPrintLine	DebugPrintf("line:%d\tfile:%s\n", __LINE__, __FILE__);

extern int DebugDisable();
extern int DebugEnable();
extern int DebugPrintf(const char* fmt, ...);

extern int WarnDisable();
extern int WarnEnable();
extern int WarnPrintf(const char* fmt, ...);

extern void ErrorPrintf(const char* fmt, ...);