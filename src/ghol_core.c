#include "holghol.h"

void gholPlainFile(const char *files[], size_t lenght) {
	int i = 0;
	for(i = 0; i < lenght; i++) {
		if(!_gholFileExist(files[i])) {
			// File not exists
			continue;
		}
		long file_size = 0;
		char *file_content = (char*) _gholFileOpen(files[i], &file_size);
		printf("%s", file_content);
	}
}

void gholLibFile(const char *files[], size_t lenght) {
	// Open file, if exist append
	// Remove headers
}
