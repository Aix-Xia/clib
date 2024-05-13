#pragma once
#ifndef _MYDIRENT_H_
#define _MYDIRENT_H_

//#define _DIRENT_IN_ENV_
#ifdef _DIRENT_IN_ENV_
#include <dirent.h>
#else
#include "../dirent/include/dirent.h"
#endif

#define WINDOWS			1
#define LINUX			2
#define UNIX			3
#define PLATFORM		WINDOWS

#if (PLATFORM == WINDOWS)
#define PATHSEPSTR		"\\"
#define PATHSEPCHAR		'\\'
#elif (PLATFORM == LINUX)
#define PATHSEPSTR		"/"
#define PATHSEPCHAR		'/'
#elif (PLATFORM == UNIX)
#define PATHSEPSTR		"/"
#define PATHSEPCHAR		'/'
#else
#define PATHSEPSTR		"/"
#define PATHSEPCHAR		'/'
#endif

//#define FILE_MAX_CNT		1024
//#define PATH_MAX_LEN		128
//#define FILE_NAME_MAX_LEN	64

extern bool FolderExist(const char* path);
extern int CreateFolder(const char* folderName);
extern int GetFiles(char* files[], const char* path);
extern int GetAllFiles(char* files[], const char* path);
extern int GetFolders(char* folders[], const char* path);
extern char* GetFileFormat(const char* filename);
extern int GetFileName(char* fileName, const char* path, bool includeExtension);

#endif
