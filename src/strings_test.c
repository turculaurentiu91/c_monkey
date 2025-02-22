#include <stdlib.h>
#include <strings.h>

#include "../lib/unity.h"
#include "strings.h"

void setUp() {}

void tearDown() {}

void test_string_new() {
    string_t str = string_new("test", 4);
    TEST_ASSERT_EQUAL_CHAR_ARRAY_MESSAGE(str.data, "test", 4, "Data does not equal \"test\"");
    TEST_ASSERT_EQUAL_UINT(4, str.length);
    TEST_ASSERT_EQUAL_CHAR('t', str.data[0]);
    TEST_ASSERT_EQUAL_CHAR('e', str.data[1]);
    TEST_ASSERT_EQUAL_CHAR('s', str.data[2]);
    TEST_ASSERT_EQUAL_CHAR('t', str.data[3]);
}


void test_string_new_from_literal() {
    string_t str = string_new_from_literal("test");
    TEST_ASSERT_EQUAL_CHAR_ARRAY_MESSAGE(str.data, "test", 4, "Data does not equal \"test\"");
    TEST_ASSERT_EQUAL_UINT(4, str.length);
    TEST_ASSERT_EQUAL_CHAR('t', str.data[0]);
    TEST_ASSERT_EQUAL_CHAR('e', str.data[1]);
    TEST_ASSERT_EQUAL_CHAR('s', str.data[2]);
    TEST_ASSERT_EQUAL_CHAR('t', str.data[3]);
}

void test_free() {
    string_t *str = malloc(sizeof(string_t));
    str->data = malloc(sizeof(char) * 10);
    str->length = 10;

    string_free(str);
}

void test_equals() {
    string_t str1 = string_new_from_literal("test-1");
    string_t str2 = string_new_from_literal("test-2");

    TEST_ASSERT_FALSE(string_equals(&str1, &str2));

    str2.data[str2.length - 1] = '1';
    TEST_ASSERT_TRUE(string_equals(&str1, &str2));
}

void test_slice_correct() {
    string_t str_main = string_new_from_literal("test-slice");
    string_t *str_slice = string_slice(5, 5, &str_main);

    string_t slice_cmp = string_new_from_literal("slice");
    TEST_ASSERT_TRUE(string_equals(str_slice, &slice_cmp));
}

void test_slice_overflow() {
    string_t str_main = string_new_from_literal("test-slice");
    string_t *str_slice = string_slice(5, 10, &str_main);

    string_t slice_cmp = string_new_from_literal("slice");
    TEST_ASSERT_TRUE(string_equals(str_slice, &slice_cmp));

    TEST_ASSERT_EQUAL_UINT(5, str_slice->length);
}


void test_slice_full() {
    string_t str_main = string_new_from_literal("test-slice");
    string_t *str_slice = string_slice(0, 10, &str_main);

    TEST_ASSERT_TRUE(string_equals(str_slice, &str_main));

    TEST_ASSERT_EQUAL_UINT(10, str_slice->length);
}

void test_to_c_string_copy() {
    string_t str_main = string_new_from_literal("test-slice");
    char *copy = malloc(sizeof(char) * 10);
    string_to_c_string_copy(copy, &str_main, 10);

    TEST_ASSERT_EQUAL_STRING_LEN("test-slice", copy, 10);

    free(copy);
}

void test_to_c_string_copy_overflow() {
    string_t str_main = string_new_from_literal("test-slice");
    char *copy = malloc(sizeof(char) * 10);
    string_to_c_string_copy(copy, &str_main, 5);

    TEST_ASSERT_EQUAL_STRING_LEN("test-", copy, 5);

    free(copy);
}

int main() {
    UNITY_BEGIN();
    RUN_TEST(test_string_new);
    RUN_TEST(test_string_new_from_literal);
    RUN_TEST(test_free);
    RUN_TEST(test_equals);
    RUN_TEST(test_slice_correct);
    RUN_TEST(test_slice_overflow);
    RUN_TEST(test_slice_full);
    RUN_TEST(test_to_c_string_copy);
    RUN_TEST(test_to_c_string_copy_overflow);
    return UNITY_END();
}
