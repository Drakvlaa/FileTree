#include <assert.h>
#include <stdio.h>
#include <stdbool.h>
#include <windows.h>
#include <time.h>

typedef struct {
	size_t files;
	size_t dirs;
} Stats;

bool isDir(const char *path) {
	const DWORD attributes = GetFileAttributes(path);
	assert(attributes != INVALID_FILE_ATTRIBUTES && "Invalid Path!");
	return (attributes & FILE_ATTRIBUTE_DIRECTORY);
}

void listFile(char *fileName, const int depth) {
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(console, FOREGROUND_BLUE);
	printf("%*c\b%s\n", depth, ' ', fileName);
	SetConsoleTextAttribute(console, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

void listDirs(char *dirPath, const int depth, Stats *stats) {
	WIN32_FIND_DATA fileData;
	HANDLE handleFind = NULL;
	char searchPath[2048];
	snprintf(searchPath, sizeof(searchPath), "%s\\*", dirPath);
	if ((handleFind = FindFirstFile(searchPath, &fileData)) == INVALID_HANDLE_VALUE) {
		fprintf(stderr, "Cannot open directory");
		return;
	}
	do {
		if (strcmp(fileData.cFileName, ".") == 0) continue;
		if (strcmp(fileData.cFileName, "..") == 0) continue;
		// create path
		snprintf(searchPath, sizeof(searchPath), "%s\\%s", dirPath, fileData.cFileName);
		// is Directory
		if (fileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
			HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(console, FOREGROUND_GREEN);
			printf("%*c\b%s:\n", depth, ' ', fileData.cFileName);
			SetConsoleTextAttribute(console, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			stats->dirs++;
			listDirs(searchPath, depth + 1, stats);
			continue;
		}
		// is File
		stats->files++;
		listFile(fileData.cFileName, depth);
	} while (FindNextFile(handleFind, &fileData));
	FindClose(handleFind);
}

int main(int argc, char **argv) {
	char* path = NULL;
	if (argc < 2) {
		fprintf(stderr, "Usage: %s <Path>\n", argv[0]);
		fprintf(stderr, "Use: %s -h or %s --help for instructions\n", argv[0], argv[0]);
		fprintf(stderr, "Use: %s -v or %s --version for version info\n", argv[0], argv[0]);
		return 1;
	}
	for (int i = 1; i < argc; ++i) {
		if (strcmp(argv[i], "--help") == 0 || strcmp(argv[i], "-h") == 0) {
			fprintf(stderr, "Usage: %s <Path>\n", argv[0]);
			exit(0);
		}
		if (strcmp(argv[i], "--version") == 0 || strcmp(argv[i], "-v") == 0) {
			fprintf(stdout, "Version 1.0 Created by Filip Sobczuk\n");
			exit(0);
		}
		if (path == NULL){
			path = argv[i];
			continue;
		}
		fprintf(stderr, "Unknown option: %s\n", argv[i]);
		return 1;
	}
	if (!isDir(path)) {
		fprintf(stderr, "Directory not found");
		return 1;
	}
	printf("%s:\n", path);
	Stats stats;
	stats.dirs = 0;
	stats.files = 0;
	const clock_t start = clock();
	listDirs(path, 2, &stats);
	const clock_t end = clock();
	double cpuTime = ((double) (end - start) / CLOCKS_PER_SEC);
	printf("Scanned: %zu directories with: %zu files\n", stats.dirs, stats.files);
	printf("Finished in: %fs", cpuTime);
	return 0;
}
