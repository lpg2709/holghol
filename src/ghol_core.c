#include "holghol.h"

void gholPlainFile(const char *files[], size_t length) {
	int i = 0;
	for(i = 0; i < length; i++) {
		if(!_gholFileExist(files[i])) {
			GHOL_PERROR("Plain text file not found: %s\n", files[i]);
			continue;
		}
		long file_size = 0;
		char *file_content = (char*) _gholFileOpen(files[i], &file_size);
		printf("%s", file_content);
	}
}

void gholLibFile(const char *files[], size_t length, const char *includes[], size_t len_includes) {
	int i = 0;
	for(i = 0; i < length; i++) {
		if(!_gholFileExist(files[i])) {
			GHOL_PERROR("Plain text file not found: %s\n", files[i]);
			continue;
		}
		long file_size = 0;
		char *file_content = (char*) _gholFileOpen(files[i], &file_size);
		const char * new_content = _gholRemoveIncludes(file_content, includes, len_includes);
		printf("%s", new_content);
		free((void*)new_content);
	}
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
