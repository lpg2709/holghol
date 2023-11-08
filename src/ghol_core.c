#include "holghol.h"

void gholPlainFile(const char *files[], size_t length, const char* outfile) {
	int i = 0;
	bool saveToFile = false;
	for(i = 0; i < length; i++) {
		if(!_gholFileExist(files[i])) {
			GHOL_PERROR("Plain text file not found: %s\n", files[i]);
			continue;
		}
		long file_size = 0;
		char *file_content = (char*) _gholFileOpen(files[i], &file_size);
		_gholFileAppendOrCreateStdout(outfile, file_content);
	}
}

void gholLibFile(const char *files[], size_t length, const char *includes[], size_t len_includes, const char* outfile) {
	int i = 0;
	for(i = 0; i < length; i++) {
		if(!_gholFileExist(files[i])) {
			GHOL_PERROR("Plain text file not found: %s\n", files[i]);
			continue;
		}
		long file_size = 0;
		char *file_content = (char*) _gholFileOpen(files[i], &file_size);
		const char * new_content = _gholRemoveIncludes(file_content, includes, len_includes);
		_gholFileAppendOrCreateStdout(outfile, new_content);
		free((void*)new_content);
	}
}

void gholCredits(const char* outfile) {
#define _GHOL_CREDIDS_STRING "//\n" \
	"// This file was generated using **holghol**\n" \
	"// Version: " GHOL_VERSION "\n" \
	"// Find more on: https://gitlab.com/lpg2709/<repo>\n" \
	"//\n"

	_gholFileAppendOrCreateStdout(outfile, _GHOL_CREDIDS_STRING);
#undef _GHOL_CREDIDS_STRING
}

void gholIfdefine(const char* prefix, const char *outfile) {
	const char* template = "\n#ifdef %s_IMPLEMENTATION\n\n";
	size_t nbytes = snprintf(NULL, 0, template, prefix) + 1;
	char* res = (char*) malloc(sizeof(char) * nbytes);
	snprintf(res, nbytes, template, prefix);
	_gholFileAppendOrCreateStdout(outfile, res);
	free(res);
}

void gholEndif(const char* prefix, const char *outfile) {
	const char* template = "\n#endif // %s_IMPLEMENTATION\n\n";
	size_t nbytes = snprintf(NULL, 0, template, prefix) + 1;
	char* res = (char*) malloc(sizeof(char) * nbytes);
	snprintf(res, nbytes, template, prefix);
	_gholFileAppendOrCreateStdout(outfile, res);
	free(res);
}
