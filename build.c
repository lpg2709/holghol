#include <stdio.h>

#include "./src/holghol.h"

int main(int argc, char **argv) {
	const char *intro[] = {
		"src/HEADER",
	};
	const char *includes_rm[] = {
		"holghol.h",
	};
	const char *api[] = {
		"src/holghol.h",
		"src/ghol_core.c",
		"src/ghol_files.c",
		"src/ghol_utils.c",
	};
	// const char *footer[] = {
	// 	"LICENCE",
	// 	"EXEMPLES",
	// };

	gholCredits();
	gholPlainFile(intro, GHOL_ARRAY_SIZE(intro));
	gholLibFile(api, GHOL_ARRAY_SIZE(api), includes_rm, GHOL_ARRAY_SIZE(includes_rm));
	//_gholRemoveIncludes("#include \"holghol.h\"\n#include \"teste.h\"\n#include \"mais.h\"\nint main() {\n  return 0; \n}", api_header, GHOL_ARRAY_SIZE(api_header));
	return 0;
}

