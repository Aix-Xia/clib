#pragma once
#ifndef _PRINTER_H_
#define _PRINTER_H_

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include "define.h"


#define	FORMAT_PRT(num)	"\033["###num##"m"

#define RESET			FORMAT_PRT(0)
// display
#define HIGHLIGHT		FORMAT_PRT(1)
#define ITALIC			FORMAT_PRT(3)
#define UNDERLINE		FORMAT_PRT(4)
#define FLICKER			FORMAT_PRT(5)
#define ANTIWHITE		FORMAT_PRT(7)
#define INVISIBLE		FORMAT_PRT(8)

// forecolor
#define BLACK_F			FORMAT_PRT(30)
#define RED_F			FORMAT_PRT(31)
#define GREEN_F			FORMAT_PRT(32)
#define YELLOW_F		FORMAT_PRT(33)
#define BLUE_F			FORMAT_PRT(34)
#define PURPLISHRED_F	FORMAT_PRT(35)
#define TURQUOISEBLUE_F	FORMAT_PRT(36)
#define	WHITE_F			FORMAT_PRT(37)

// backcolor
#define BLACK_B			FORMAT_PRT(40)
#define RED_B			FORMAT_PRT(41)
#define GREEN_B			FORMAT_PRT(42)
#define YELLOW_B		FORMAT_PRT(43)
#define BLUE_B			FORMAT_PRT(44)
#define PURPLISHRED_B	FORMAT_PRT(45)
#define TURQUOISEBLUE_B	FORMAT_PRT(46)
#define	WHITE_B			FORMAT_PRT(47)


#define BUFSIZE			1024
#define DebugPrintLine	DebugPrintf("line:%d\tfile:%s\n", __LINE__, __FILE__);

extern int SetPrinter(int num_args, ...);
extern int ResetPrinter();

extern int DebugDisable();
extern int DebugEnable();
extern int DebugPrintf(const char* fmt, ...);

extern int WarnDisable();
extern int WarnEnable();
extern int WarnPrintf(const char* fmt, ...);

extern void ErrorPrintf(const char* fmt, ...);

#endif
