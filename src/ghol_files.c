#include "holghol.h"

const char* _gholFileOpen(const char *filepath, long *filesize) {
	FILE *f = fopen(filepath, "r");
	const char *filecontent;

	if(f == NULL) {
		GHOL_PERROR("Fail to open the file '%s'\n", filepath);
		exit(EXIT_FAILURE);
	}

	fseek(f, 0L, SEEK_END);
	*filesize = ftell(f);
	fseek(f, 0L, SEEK_SET);

	if(*filesize == 1) {
		GHOL_PERROR("No content on file '%s'\n", filepath);
		exit(EXIT_FAILURE);
	}

	filecontent = (char *) malloc(sizeof(char) * (*filesize + 1));

	if(filecontent == NULL) {
		GHOL_PERROR("Fail to allocate memory for '%s' content!\n", filepath);
		exit(EXIT_FAILURE);
	}

	fread((void*) filecontent, 1, *filesize, f);

	fclose(f);

	return filecontent;
}

bool _gholFileCreate(const char *filepath, const char *content) {
	FILE *f = fopen(filepath, "w");
	const char *filecontent;

	if(f == NULL) {
		GHOL_PERROR("Fail to open the file '%s' for write!\n", filepath);
		exit(EXIT_FAILURE);
	}

	int size = fprintf(f, "%s", content);
	fclose(f);

	if(size < 0) {
		return false;
	}

	return true;
}

bool _gholFileAppend(const char *filepath, const char *content) {
	FILE *f = fopen(filepath, "a");
	const char *filecontent;

	if(f == NULL) {
		GHOL_PERROR("Fail to open the file '%s' for appending!\n", filepath);
		exit(EXIT_FAILURE);
	}

	int size = fprintf(f, "%s", content);
	fclose(f);

	if(size < 0) {
		return false;
	}

	return true;
}

bool _gholFileExist(const char *filepath) {
	FILE *file = fopen(filepath, "r");
	if (file != NULL) {
		fclose(file);
		return true;
	}
	return false;
}

void _gholFileAppendOrCreateStdout(const char *filepath, const char *content) {
	if(filepath != NULL) {
		if(_gholFileExist(filepath)) {
			_gholFileAppend(filepath, content);
		} else {
			_gholFileCreate(filepath, content);
		}
	} else {
		fprintf(stdout, "%s", content);
	}
}
