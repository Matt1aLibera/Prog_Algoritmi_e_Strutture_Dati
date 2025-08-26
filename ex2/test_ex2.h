#ifndef TEST_EX2_H
#define TEST_EX2_H

#include "edit_distance.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <limits.h>

// Test utility functions
void assert_edit_distance(const char *s1, const char *s2, int expected, const char *test_name);
void assert_null_handling(void);

// Test cases
void test_empty_strings(void);
void test_first_string_empty(void);
void test_second_string_empty(void);
void test_equal_strings(void);
void test_single_deletion(void);
void test_single_insertion(void);
void test_multiple_operations(void);
void test_completely_different_strings(void);
void test_substring_relationships(void);
void test_prefix_suffix_cases(void);
void test_single_char_strings(void);
void test_consistency_across_functions(void);
void test_min_functions(void);

#endif