#ifndef TEST_SORTING_H
#define TEST_SORTING_H

#include "sorting_algorithms.h"
#include <stddef.h>

// ==================== TEST FUNCTION DECLARATIONS ====================

// Test functions for Merge Sort
void test_merge_sort_empty_array(void);
void test_merge_sort_single_element(void);
void test_merge_sort_already_sorted(void);
void test_merge_sort_reverse_sorted(void);
void test_merge_sort_random_order(void);
void test_merge_sort_with_duplicates(void);
void test_merge_sort_chars(void);

// Test functions for Quick Sort
void test_quick_sort_empty_array(void);
void test_quick_sort_single_element(void);
void test_quick_sort_already_sorted(void);
void test_quick_sort_reverse_sorted(void);
void test_quick_sort_random_order(void);
void test_quick_sort_with_duplicates(void);
void test_quick_sort_chars(void);

// Comparative tests
void test_both_sorts_produce_same_result(void);

// Edge cases tests
void test_large_array(void);

// Utility functions tests
void test_swap_function(void);
void test_swap_chars(void);

// ==================== COMPARISON FUNCTIONS ====================

/**
 * @brief Comparison function for integers
 * @return negative if a < b, zero if a == b, positive if a > b
 */
int compare_int(const void *a, const void *b);

/**
 * @brief Comparison function for characters  
 * @return negative if a < b, zero if a == b, positive if a > b
 */
int compare_char(const void *a, const void *b);

// ==================== TEST UTILITY FUNCTIONS ====================

/**
 * @brief Helper function to compare integer arrays and print results
 * @param expected Expected array
 * @param actual Actual array  
 * @param size Size of arrays
 * @param test_name Name of the test for output
 */
void assert_equal_int_array(const int *expected, const int *actual, size_t size, const char *test_name);

/**
 * @brief Helper function to compare character arrays and print results
 * @param expected Expected array
 * @param actual Actual array
 * @param size Size of arrays
 * @param test_name Name of the test for output
 */
void assert_equal_char_array(const char *expected, const char *actual, size_t size, const char *test_name);

#endif // TEST_SORTING_H