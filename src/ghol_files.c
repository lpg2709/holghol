#include "holghol.h"

const char* gholOpenFile(const char *filepath, long *filesize) {
	FILE *f = fopen(filepath, "r");
	const char *filecontent;

	if(f == NULL) {
		fprintf(stderr, "Error: fail to open the file '%s'\n", filepath);
		exit(EXIT_FAILURE);
	}

	fseek(f, 0L, SEEK_END);
	*filesize = ftell(f);
	fseek(f, 0L, SEEK_SET);

	if(*filesize == 1) {
		fprintf(stderr, "Error: no content on file '%s'\n", filepath);
		exit(EXIT_FAILURE);
	}

	filecontent = (char *) malloc(sizeof(char) * (*filesize + 1));

	if(filecontent == NULL) {
		fprintf(stderr, "Error: fail to allocate memory for file content!\n");
		exit(EXIT_FAILURE);
	}

	fread((void*) filecontent, 1, *filesize, f);

	fclose(f);

	return filecontent;
}

