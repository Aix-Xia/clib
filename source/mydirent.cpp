#include "../header/mydirent.h"




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
			strcpy(files[i], path);
			strcat(files[i], "/");
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
			strcpy(files[i], path);
			strcat(files[i], "/");
			strcat(files[i], entry->d_name);
			i++;
		}
		else if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
			continue;
		}
		else if (entry->d_type == DT_DIR) {
			char* folder = (char*)malloc(strlen(path) + strlen(entry->d_name) + 2);
			strcpy(folder, path);
			strcat(folder, "/");
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
			strcpy(folders[i], path);
			strcat(folders[i], "/");
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