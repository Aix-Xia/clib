#include "../header/mydirent.h"


bool FolderExist(const char* path) {
	DIR* dir = opendir(path);
	if (dir) {
		closedir(dir);
		return true;
	}
	return false;
}
int CreateFolder(const char* path) {
	char buffer[128];

	sprintf(buffer, "MD %s", path);
	system(buffer);

	return 0;
}

int GetFiles(char* files[], const char* path) {
	struct dirent* entry;
	DIR* dir = opendir(path);	// 打开文件夹
	int i = 0;

	if (dir == NULL) {
		perror("opendir");
		return -1;
	}

	while ((entry = readdir(dir)) != NULL) {
		if (entry->d_type == DT_REG) { // 如果是普通文件
			files[i] = (char*)malloc(strlen(path) + strlen(entry->d_name) + 2);
			if (files[i] == NULL) {
				perror("files[i]");
				return -1;
			}
			strcpy(files[i], path);
			strcat(files[i], PATHSEPSTR);
			strcat(files[i], entry->d_name);
			i++;
		}
	}

	closedir(dir);// 关闭文件夹

	return i;
}

int GetAllFiles(char* files[], const char* path) {
	struct dirent* entry;
	DIR* dir = opendir(path);	// 打开文件夹
	int i = 0;

	if (dir == NULL) {
		perror("opendir");
		return -1;
	}

	while ((entry = readdir(dir)) != NULL) {
		if (entry->d_type == DT_REG) { // 如果是普通文件
			files[i] = (char*)malloc(strlen(path) + strlen(entry->d_name) + 2);
			if (files[i] == NULL) {
				perror("files[i]");
				return -1;
			}
			strcpy(files[i], path);
			strcat(files[i], PATHSEPSTR);
			strcat(files[i], entry->d_name);
			i++;
		}
		else if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
			continue;
		}
		else if (entry->d_type == DT_DIR) {
			char* folder = (char*)malloc(strlen(path) + strlen(entry->d_name) + 2);
			if (folder == NULL) {
				perror("folder");
				return -1;
			}
			strcpy(folder, path);
			strcat(folder, PATHSEPSTR);
			strcat(folder, entry->d_name);
			i += GetAllFiles(files + i, folder);
		}
	}

	return i;
}

int GetFolders(char* folders[], const char* path) {
	struct dirent* entry;
	DIR* dir = opendir(path);	// 打开文件夹
	int i = 0;

	if (dir == NULL) {
		perror("opendir");
		return -1;
	}

	while ((entry = readdir(dir)) != NULL) {
		if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
			continue;
		}
		if (entry->d_type == DT_DIR) { // 如果文件夹
			folders[i] = (char*)malloc(strlen(path) + strlen(entry->d_name) + 2);
			if (folders[i] == NULL) {
				perror("folder");
				return -1;
			}
			strcpy(folders[i], path);
			strcat(folders[i], PATHSEPSTR);
			strcat(folders[i], entry->d_name);
			i++;
		}
	}

	closedir(dir);// 关闭文件夹

	return i;
}

char* GetFileFormat(const char* filename) {
	const char* dot = strrchr(filename, '.');
	if (dot && dot != filename) {
		static char format[10];
		strncpy(format, dot + 1, sizeof(format) - 1);
		format[sizeof(format) - 1] = '\0';
		return format;
	}
	return NULL;
}

int GetFileName(char* fileName, const char* path, bool includeExtension) {
	const char* lastSlash = strrchr(path, PATHSEPCHAR); // Unix/Linux-styple path
	if (lastSlash != NULL) {
		const char* nameStart = lastSlash + 1;
		strcpy(fileName, nameStart);
		if(!includeExtension){
			char* dot = (char *)strrchr(fileName, '.');
			if (dot != NULL) {
				*dot = '\0';
			}
		}
	}
	else {
		strcpy(fileName, path);
	}
	return (int)strlen(fileName);
}
