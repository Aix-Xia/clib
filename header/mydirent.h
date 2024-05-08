#pragma once

//#define _DIRENT_IN_ENV_
#ifdef _DIRENT_IN_ENV_
#include <dirent.h>
#else
#include "../dirent/include/dirent.h"
#endif


#define FILE_MAX_CNT	1024
#define PATH_STR_LEN	128


int GetFiles(char* files[], const char* path);
int GetAllFiles(char* files[], const char* path);
int GetFolders(char* folders[], const char* path);
char* GetFileFormat(const char* filename);