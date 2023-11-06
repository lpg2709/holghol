#include <stdio.h>

#include "./src/holghol.h"

void gholPlainFile(const char *files[], size_t lenght) {
	printf("Plan: \n");
	int i = 0;
	for(i = 0; i < lenght; i++) {
		printf("- %s\n", files[i]);
	}
}

void gholLibFile(const char *files[], size_t lenght) {
	printf("lib: \n");
	int i = 0;
	for(i = 0; i < lenght; i++) {
		printf("- %s\n", files[i]);
	}
}

int main(int argc, char **argv) {
	const char *intro[] = {
		"HEADER",
	};
	const char *api[] = {
		"holghol.h",
	};
	const char *footer[] = {
		"LICENCE",
		"EXEMPLES",
	};

	gholPlainFile(intro, GHOL_ARRAY_SIZE(intro));
	gholLibFile(api, GHOL_ARRAY_SIZE(api));
	gholPlainFile(footer, GHOL_ARRAY_SIZE(footer));
	return 0;
}

