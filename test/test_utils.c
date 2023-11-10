#include "../src/holghol.h"
#include "unity/unity.h"
#include "unity/unity_internals.h"

void setUp() {}

void tearDown() {}

void test_remove_include_uncheged() {
	const char string[19] = "#include <stdio.h>\n";
	const char *includes[] = {
		"holghol.h",
	};
	const char *result = _gholRemoveIncludes(string, sizeof(char) * 19, includes, GHOL_ARRAY_SIZE(includes));
	TEST_ASSERT_EQUAL_STRING(string, result);
	free((void*) result);

	const char string2[70] = "#include \"my_lib.h\"\n"
							 "#include \"lib2.h\"\n"
							 "int main() {\n"
							 "	return 0;\n"
							 "}\n";
	const char *result2 = _gholRemoveIncludes(string2, sizeof(char) * 70, includes, GHOL_ARRAY_SIZE(includes));
	TEST_ASSERT_EQUAL_STRING(string2, result2);
	free((void*) result2);
}

void test_remove_include_uncheged_long() {
	const char string[70] = "#include \"my_lib.h\"\n"
							 "#include \"lib2.h\"\n"
							 "int main() {\n"
							 "	return 0;\n"
							 "}\n";
	const char *includes[] = {
		"holghol.h",
	};
	const char *result = _gholRemoveIncludes(string, sizeof(char) * 70, includes, GHOL_ARRAY_SIZE(includes));
	TEST_ASSERT_EQUAL_STRING(string, result);
	free((void*) result);
}

void test_remove_include_one_remove() {
	const char string[70] = "#include \"my_lib.h\"\n"
							 "#include \"holghol.h\"\n"
							 "int main() {\n"
							 "	return 0;\n"
							 "}\n";
	const char expected[70] = "#include \"my_lib.h\"\n"
							  "                      \n"
							  "int main() {\n"
							  "	return 0;\n"
							  "}\n";
	const char *includes[] = {
		"holghol.h",
	};
	const char *result = _gholRemoveIncludes(string, sizeof(char) * 70, includes, GHOL_ARRAY_SIZE(includes));
	TEST_ASSERT_EQUAL_STRING(expected, result);
	free((void*) result);
}

void test_remove_include_more_then_one_remove() {
	const char string[70] = "#include \"my_lib.h\"\n"
							 "#include \"holghol.h\"\n"
							 "int main() {\n"
							 "	return 0;\n"
							 "}\n";
	const char expected[70] = "                   \n"
							  "                    \n"
							  "int main() {\n"
							  "	return 0;\n"
							  "}\n";
	const char *includes[] = {
		"holghol.h",
		"my_lib.h"
	};
	const char *result = _gholRemoveIncludes(string, sizeof(char) * 70, includes, GHOL_ARRAY_SIZE(includes));
	TEST_ASSERT_EQUAL_STRING(expected, result);
	free((void*) result);
}

int main() {
	UNITY_BEGIN();
	RUN_TEST(test_remove_include_uncheged);
	RUN_TEST(test_remove_include_uncheged_long);
	RUN_TEST(test_remove_include_more_then_one_remove);
	return UNITY_END();
}
