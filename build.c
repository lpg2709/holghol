#include <stdio.h>

#include "./src/holghol.h"

int main(int argc, char **argv) {
	const char *output = "../holghol.h";
	//const char *output = NULL; // Print to stdou

	const char *intro[] = {
        "../src/HEADER",
	};
	const char *includes_rm[] = {
		"holghol.h",
	};
	const char *api[] = {
		"../src/holghol.h",
        "../src/ghol_core.c",
        "../src/ghol_files.c",
        "../src/ghol_utils.c",
	};
	const char *footer[] = {
		"../src/CHANGELOG",
		"../src/CREDITS",
		"../src/LICENSE",
	};

	gholCredits(output);
	gholPlainFile(intro, GHOL_ARRAY_SIZE(intro), output);
	gholIfdefine("HOLGHOL", output);
	gholLibFile(api, GHOL_ARRAY_SIZE(api), includes_rm, GHOL_ARRAY_SIZE(includes_rm), output);
	gholEndif("HOLGHOL", output);
	gholPlainFile(footer, GHOL_ARRAY_SIZE(footer), output);

	return 0;
}

