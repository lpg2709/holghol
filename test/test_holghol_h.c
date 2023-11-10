#include "../src/holghol.h"
#include "unity/unity.h"
#include "unity/unity_internals.h"

void setUp() {}

void tearDown() {}

void test_array_size_int_right() {
	int i_array[3] = {1, 2, 3};
	TEST_ASSERT_EQUAL_INT(3, GHOL_ARRAY_SIZE(i_array));
}

void test_array_size_string_right() {
	const char *c_array[] = {
		"one", "simple", "array"
	};
	TEST_ASSERT_EQUAL_INT(3, GHOL_ARRAY_SIZE(c_array));
}

void test_version() {
	TEST_ASSERT_EQUAL_STRING("0.1.0", GHOL_VERSION);
}

int main() {
	UNITY_BEGIN();
	RUN_TEST(test_array_size_int_right);
	RUN_TEST(test_array_size_string_right);
	RUN_TEST(test_version);
	return UNITY_END();
}

