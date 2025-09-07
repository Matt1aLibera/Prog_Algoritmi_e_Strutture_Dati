/**
 * @file test_ex2.h
 * @brief Test suite for edit distance algorithms implementation
 * 
 * This header provides comprehensive test functions for validating
 * the edit distance algorithms implemented in edit_distance.h.
 * Includes tests for various edge cases, boundary conditions, and
 * functional verification of both recursive and dynamic programming approaches.
 */

#ifndef TEST_EX2_H
#define TEST_EX2_H

#include "edit_distance.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <limits.h>

/**
 * @defgroup TestUtilities Test Utility Functions
 * @brief Helper functions for test validation and assertion
 * @{
 */

/**
 * @brief Asserts that edit distance calculation matches expected value
 * 
 * Validates that both recursive and dynamic programming implementations
 * return the expected edit distance for given input strings.
 * 
 * @param s1 First input string for edit distance calculation
 * @param s2 Second input string for edit distance calculation
 * @param expected Expected edit distance value
 * @param test_name Name of the test case for identification in output
 */
void assert_edit_distance(const char *s1, const char *s2, int expected, const char *test_name);

/**
 * @brief Tests proper handling of NULL input parameters
 * 
 * Verifies that both edit distance functions correctly handle NULL inputs
 * by returning the expected error value (-1).
 */
void assert_null_handling(void);

/** @} */ // End of TestUtilities group

/**
 * @defgroup BasicTests Basic Functionality Tests
 * @brief Tests for fundamental edit distance functionality
 * @{
 */

/**
 * @brief Tests edit distance with empty strings
 */
void test_empty_strings(void);

/**
 * @brief Tests edit distance when first string is empty
 */
void test_first_string_empty(void);

/**
 * @brief Tests edit distance when second string is empty
 */
void test_second_string_empty(void);

/**
 * @brief Tests edit distance with identical strings
 */
void test_equal_strings(void);

/**
 * @brief Tests edit distance requiring single deletion operation
 */
void test_single_deletion(void);

/**
 * @brief Tests edit distance requiring single insertion operation
 */
void test_single_insertion(void);

/**
 * @brief Tests edit distance requiring multiple operations
 */
void test_multiple_operations(void);

/** @} */ // End of BasicTests group

/**
 * @defgroup EdgeCaseTests Edge Case Tests
 * @brief Tests for boundary conditions and edge cases
 * @{
 */

/**
 * @brief Tests edit distance with completely different strings
 */
void test_completely_different_strings(void);

/**
 * @brief Tests edit distance with substring relationships
 */
void test_substring_relationships(void);

/**
 * @brief Tests edit distance with prefix and suffix cases
 */
void test_prefix_suffix_cases(void);

/**
 * @brief Tests edit distance with single character strings
 */
void test_single_char_strings(void);

/** @} */ // End of EdgeCaseTests group

/**
 * @defgroup ConsistencyTests Consistency Tests
 * @brief Tests for consistency across implementations
 * @{
 */

/**
 * @brief Tests consistency between recursive and dynamic programming implementations
 * 
 * Verifies that both edit_distance() and edit_distance_dyn() return
 * identical results for the same input strings.
 */
void test_consistency_across_functions(void);

/** @} */ // End of ConsistencyTests group

/**
 * @defgroup UtilityTests Utility Function Tests
 * @brief Tests for helper and utility functions
 * @{
 */

/**
 * @brief Tests the min3 utility function
 * 
 * Verifies that the min3 function correctly returns the minimum
 * of three integer values in various scenarios.
 */
void test_min_functions(void);

/** @} */ // End of UtilityTests group

#endif /* TEST_EX2_H */