#include "holghol.h"

void gholPlainFile(const char *files[], size_t length) {
	int i = 0;
	for(i = 0; i < length; i++) {
		if(!_gholFileExist(files[i])) {
			// File not exists
			continue;
		}
		long file_size = 0;
		char *file_content = (char*) _gholFileOpen(files[i], &file_size);
		printf("%s", file_content);
	}
}

void gholLibFile(const char *files[], size_t length) {
	// Open file, if exist append
	// Remove headers
}

void gholCredits() {
	fprintf(stdout,
		"//\n"
		"// This file was generated using **holghol**\n"
		"// Version: %s\n"
		"// Find more on: https://gitlab.com/lpg2709/<repo>\n"
		"//\n",
		GHOL_VERSION);
}
