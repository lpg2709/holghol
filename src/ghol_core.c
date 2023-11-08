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
		if(outfile != NULL) {
			if(_gholFileExist(outfile)) {
				_gholFileAppend(outfile, file_content);
			} else {
				_gholFileCreate(outfile, file_content);
			}
		} else {
			fprintf(stdout, "%s", file_content);
		}
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
		if(outfile != NULL) {
			if(_gholFileExist(outfile)) {
				_gholFileAppend(outfile, new_content);
			} else {
				_gholFileCreate(outfile, new_content);
			}
		} else {
			fprintf(stdout, "%s", new_content);
		}
		free((void*)new_content);
	}
}

void gholCredits(const char* outfile) {
#define _GHOL_CREDIDS_STRING "//\n" \
					"// This file was generated using **holghol**\n" \
				 	"// Version: " GHOL_VERSION "\n" \
				 	"// Find more on: https://gitlab.com/lpg2709/<repo>\n" \
				 	"//\n"

	if(outfile != NULL) {
		if(_gholFileExist(outfile)) {
			_gholFileAppend(outfile, _GHOL_CREDIDS_STRING);
		} else {
			_gholFileCreate(outfile, _GHOL_CREDIDS_STRING);
		}
	} else {
		fprintf(stdout, "%s", _GHOL_CREDIDS_STRING);
	}
#undef _GHOL_CREDIDS_STRING
}
