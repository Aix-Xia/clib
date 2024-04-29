#pragma once
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#define COMPLETE		0
#define IMCOMPLETE		1
#define ABNORMAL		2

#define BUFSIZE		1024


extern int DebugDisable();
extern int DebugEnable();
extern int DebugPrintf(const char* fmt, ...);

extern int WarnDisable();
extern int WarnEnable();
extern int WarnPrintf(const char* fmt, ...);

extern void ErrorPrintf(const char* fmt, ...);



