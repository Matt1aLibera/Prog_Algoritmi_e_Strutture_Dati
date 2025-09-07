/**
 * @file test_sorting.h
 * @brief Test suite for sorting algorithms implementation
 * 
 * This header provides comprehensive test functions for validating
 * the Merge Sort and Quick Sort algorithms implemented in sorting_algorithms.h.
 * Includes tests for various edge cases, comparative tests, and utility functions.
 */

#ifndef TEST_SORTING_H
#define TEST_SORTING_H

#include "sorting_algorithms.h"
#include <stddef.h>

// ==================== TEST FUNCTION DECLARATIONS ====================

/**
 * @defgroup MergeSortTests Merge Sort Test Functions
 * @brief Test functions specific to Merge Sort algorithm
 * @{
 */

/**
 * @brief Tests Merge Sort with an empty array
 */
void test_merge_sort_empty_array(void);

/**
 * @brief Tests Merge Sort with a single element array
 */
void test_merge_sort_single_element(void);

/**
 * @brief Tests Merge Sort with an already sorted array
 */
void test_merge_sort_already_sorted(void);

/**
 * @brief Tests Merge Sort with a reverse sorted array
 */
void test_merge_sort_reverse_sorted(void);

/**
 * @brief Tests Merge Sort with a randomly ordered array
 */
void test_merge_sort_random_order(void);

/**
 * @brief Tests Merge Sort with duplicate elements
 */
void test_merge_sort_with_duplicates(void);

/**
 * @brief Tests Merge Sort with character arrays
 */
void test_merge_sort_chars(void);

/** @} */ // End of MergeSortTests group

/**
 * @defgroup QuickSortTests Quick Sort Test Functions
 * @brief Test functions specific to Quick Sort algorithm
 * @{
 */

/**
 * @brief Tests Quick Sort with an empty array
 */
void test_quick_sort_empty_array(void);

/**
 * @brief Tests Quick Sort with a single element array
 */
void test_quick_sort_single_element(void);

/**
 * @brief Tests Quick Sort with an already sorted array
 */
void test_quick_sort_already_sorted(void);

/**
 * @brief Tests Quick Sort with a reverse sorted array
 */
void test_quick_sort_reverse_sorted(void);

/**
 * @brief Tests Quick Sort with a randomly ordered array
 */
void test_quick_sort_random_order(void);

/**
 * @brief Tests Quick Sort with duplicate elements
 */
void test_quick_sort_with_duplicates(void);

/**
 * @brief Tests Quick Sort with character arrays
 */
void test_quick_sort_chars(void);

/** @} */ // End of QuickSortTests group

/**
 * @defgroup ComparativeTests Comparative Test Functions
 * @brief Tests comparing both sorting algorithms
 * @{
 */

/**
 * @brief Verifies that both algorithms produce identical results
 * 
 * Tests that Merge Sort and Quick Sort produce the same output
 * for various input arrays, ensuring consistency between algorithms.
 */
void test_both_sorts_produce_same_result(void);

/** @} */ // End of ComparativeTests group

/**
 * @defgroup EdgeCaseTests Edge Case Test Functions
 * @brief Tests for boundary conditions and edge cases
 * @{
 */

/**
 * @brief Tests sorting performance with large arrays
 * 
 * Validates that both algorithms can handle large input sizes
 * without crashing or producing incorrect results.
 */
void test_large_array(void);

/** @} */ // End of EdgeCaseTests group

/**
 * @defgroup UtilityTests Utility Function Tests
 * @brief Tests for helper and utility functions
 * @{
 */

/**
 * @brief Tests the swap function with integer data
 */
void test_swap_function(void);

/**
 * @brief Tests the swap function with character data
 */
void test_swap_chars(void);

/** @} */ // End of UtilityTests group

// ==================== COMPARISON FUNCTIONS ====================

/**
 * @brief Comparison function for integers
 * 
 * Standard integer comparison function for use with sorting algorithms.
 * 
 * @param a Pointer to first integer
 * @param b Pointer to second integer
 * @return negative if a < b, zero if a == b, positive if a > b
 */
int compare_int(const void *a, const void *b);

/**
 * @brief Comparison function for characters
 * 
 * Standard character comparison function for use with sorting algorithms.
 * 
 * @param a Pointer to first character
 * @param b Pointer to second character
 * @return negative if a < b, zero if a == b, positive if a > b
 */
int compare_char(const void *a, const void *b);

// ==================== TEST UTILITY FUNCTIONS ====================

/**
 * @brief Helper function to compare integer arrays and print results
 * 
 * Compares two integer arrays and prints detailed error information
 * if they differ. Used for test validation.
 * 
 * @param expected Expected array values
 * @param actual Actual array values obtained from sorting
 * @param size Number of elements in the arrays
 * @param test_name Name of the test case for output identification
 */
void assert_equal_int_array(const int *expected, const int *actual, size_t size, const char *test_name);

/**
 * @brief Helper function to compare character arrays and print results
 * 
 * Compares two character arrays and prints detailed error information
 * if they differ. Used for test validation with character data.
 * 
 * @param expected Expected array values
 * @param actual Actual array values obtained from sorting
 * @param size Number of elements in the arrays
 * @param test_name Name of the test case for output identification
 */
void assert_equal_char_array(const char *expected, const char *actual, size_t size, const char *test_name);

#endif // TEST_SORTING_H