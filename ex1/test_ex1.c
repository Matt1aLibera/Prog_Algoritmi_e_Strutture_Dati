#include "test_ex1.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

// ==================== COMPARISON FUNCTIONS ====================

int compare_int(const void *a, const void *b) {
    int int_a = *((int*)a);
    int int_b = *((int*)b);
    return (int_a > int_b) - (int_a < int_b);
}

int compare_char(const void *a, const void *b) {
    char char_a = *((char*)a);
    char char_b = *((char*)b);
    return (char_a > char_b) - (char_a < char_b);
}

// ==================== TEST UTILITY FUNCTIONS ====================

void assert_equal_int_array(const int *expected, const int *actual, size_t size, const char *test_name) {
    for (size_t i = 0; i < size; i++) {
        if (expected[i] != actual[i]) {
            printf("FAIL: %s - Expected [", test_name);
            for (size_t j = 0; j < size; j++) printf("%d ", expected[j]);
            printf("] but got [");
            for (size_t j = 0; j < size; j++) printf("%d ", actual[j]);
            printf("]\n");
            assert(0);
        }
    }
    printf("PASS: %s\n", test_name);
}

void assert_equal_char_array(const char *expected, const char *actual, size_t size, const char *test_name) {
    for (size_t i = 0; i < size; i++) {
        if (expected[i] != actual[i]) {
            printf("FAIL: %s - Expected [", test_name);
            for (size_t j = 0; j < size; j++) printf("%c ", expected[j]);
            printf("] but got [");
            for (size_t j = 0; j < size; j++) printf("%c ", actual[j]);
            printf("]\n");
            assert(0);
        }
    }
    printf("PASS: %s\n", test_name);
}

// ==================== TEST MERGE SORT ====================

void test_merge_sort_empty_array(void) {
    int arr[] = {};
    
    merge_sort(arr, 0, sizeof(int), compare_int);
    printf("PASS: test_merge_sort_empty_array\n");
}

void test_merge_sort_single_element(void) {
    int arr[] = {42};
    int expected[] = {42};
    
    merge_sort(arr, 1, sizeof(int), compare_int);
    assert_equal_int_array(expected, arr, 1, "test_merge_sort_single_element");
}

void test_merge_sort_already_sorted(void) {
    int arr[] = {1, 2, 3, 4, 5};
    int expected[] = {1, 2, 3, 4, 5};
    
    merge_sort(arr, 5, sizeof(int), compare_int);
    assert_equal_int_array(expected, arr, 5, "test_merge_sort_already_sorted");
}

void test_merge_sort_reverse_sorted(void) {
    int arr[] = {5, 4, 3, 2, 1};
    int expected[] = {1, 2, 3, 4, 5};
    
    merge_sort(arr, 5, sizeof(int), compare_int);
    assert_equal_int_array(expected, arr, 5, "test_merge_sort_reverse_sorted");
}

void test_merge_sort_random_order(void) {
    int arr[] = {3, 1, 4, 1, 5, 9, 2, 6};
    int expected[] = {1, 1, 2, 3, 4, 5, 6, 9};
    
    merge_sort(arr, 8, sizeof(int), compare_int);
    assert_equal_int_array(expected, arr, 8, "test_merge_sort_random_order");
}

void test_merge_sort_with_duplicates(void) {
    int arr[] = {5, 2, 8, 2, 5, 1, 8};
    int expected[] = {1, 2, 2, 5, 5, 8, 8};
    
    merge_sort(arr, 7, sizeof(int), compare_int);
    assert_equal_int_array(expected, arr, 7, "test_merge_sort_with_duplicates");
}

void test_merge_sort_chars(void) {
    char arr[] = {'z', 'a', 'm', 'b', 'a'};
    char expected[] = {'a', 'a', 'b', 'm', 'z'};
    
    merge_sort(arr, 5, sizeof(char), compare_char);
    assert_equal_char_array(expected, arr, 5, "test_merge_sort_chars");
}

// ==================== TEST QUICK SORT ====================

void test_quick_sort_empty_array(void) {
    int arr[] = {};
    
    quick_sort(arr, 0, sizeof(int), compare_int);
    printf("PASS: test_quick_sort_empty_array\n");
}

void test_quick_sort_single_element(void) {
    int arr[] = {42};
    int expected[] = {42};
    
    quick_sort(arr, 1, sizeof(int), compare_int);
    assert_equal_int_array(expected, arr, 1, "test_quick_sort_single_element");
}

void test_quick_sort_already_sorted(void) {
    int arr[] = {1, 2, 3, 4, 5};
    int expected[] = {1, 2, 3, 4, 5};
    
    quick_sort(arr, 5, sizeof(int), compare_int);
    assert_equal_int_array(expected, arr, 5, "test_quick_sort_already_sorted");
}

void test_quick_sort_reverse_sorted(void) {
    int arr[] = {5, 4, 3, 2, 1};
    int expected[] = {1, 2, 3, 4, 5};
    
    quick_sort(arr, 5, sizeof(int), compare_int);
    assert_equal_int_array(expected, arr, 5, "test_quick_sort_reverse_sorted");
}

void test_quick_sort_random_order(void) {
    int arr[] = {3, 1, 4, 1, 5, 9, 2, 6};
    int expected[] = {1, 1, 2, 3, 4, 5, 6, 9};
    
    quick_sort(arr, 8, sizeof(int), compare_int);
    assert_equal_int_array(expected, arr, 8, "test_quick_sort_random_order");
}

void test_quick_sort_with_duplicates(void) {
    int arr[] = {5, 2, 8, 2, 5, 1, 8};
    int expected[] = {1, 2, 2, 5, 5, 8, 8};
    
    quick_sort(arr, 7, sizeof(int), compare_int);
    assert_equal_int_array(expected, arr, 7, "test_quick_sort_with_duplicates");
}

void test_quick_sort_chars(void) {
    char arr[] = {'z', 'a', 'm', 'b', 'a'};
    char expected[] = {'a', 'a', 'b', 'm', 'z'};
    
    quick_sort(arr, 5, sizeof(char), compare_char);
    assert_equal_char_array(expected, arr, 5, "test_quick_sort_chars");
}

// ==================== TEST COMPARAZIONE ALGORITMI ====================

void test_both_sorts_produce_same_result(void) {
    int arr1[] = {9, 3, 7, 1, 5, 2, 8, 4, 6};
    int arr2[] = {9, 3, 7, 1, 5, 2, 8, 4, 6};
    int expected[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    
    merge_sort(arr1, 9, sizeof(int), compare_int);
    quick_sort(arr2, 9, sizeof(int), compare_int);
    
    assert_equal_int_array(expected, arr1, 9, "test_both_sorts_merge_result");
    assert_equal_int_array(expected, arr2, 9, "test_both_sorts_quick_result");
    
    // Verifica che entrambi gli array siano uguali
    for (int i = 0; i < 9; i++) {
        if (arr1[i] != arr2[i]) {
            printf("FAIL: test_both_sorts_produce_same_result - Results differ at index %d\n", i);
            assert(0);
        }
    }
    printf("PASS: test_both_sorts_produce_same_result\n");
}

// ==================== TEST EDGE CASES ====================

void test_large_array(void) {
    const int SIZE = 1000;
    int *arr = malloc(SIZE * sizeof(int));
    int *expected = malloc(SIZE * sizeof(int));
    
    // Riempie array con numeri in ordine decrescente
    for (int i = 0; i < SIZE; i++) {
        arr[i] = SIZE - i - 1;
        expected[i] = i;
    }
    
    quick_sort(arr, SIZE, sizeof(int), compare_int);
    assert_equal_int_array(expected, arr, SIZE, "test_large_array");
    
    free(arr);
    free(expected);
}

// ==================== TEST FUNZIONI DI SUPPORTO ====================

void test_swap_function(void) {
    int a = 10, b = 20;
    swap(&a, &b, sizeof(int));
    
    if (a != 20 || b != 10) {
        printf("FAIL: test_swap_function - Expected a=20, b=10 but got a=%d, b=%d\n", a, b);
        assert(0);
    }
    printf("PASS: test_swap_function\n");
}

void test_swap_chars(void) {
    char c1 = 'A', c2 = 'B';
    swap(&c1, &c2, sizeof(char));
    
    if (c1 != 'B' || c2 != 'A') {
        printf("FAIL: test_swap_chars - Expected c1=B, c2=A but got c1=%c, c2=%c\n", c1, c2);
        assert(0);
    }
    printf("PASS: test_swap_chars\n");
}

// ==================== MAIN TEST RUNNER ====================

int main(void) {
    printf("=== Running Sorting Algorithm Tests ===\n\n");
    
    // Test Merge Sort
    test_merge_sort_empty_array();
    test_merge_sort_single_element();
    test_merge_sort_already_sorted();
    test_merge_sort_reverse_sorted();
    test_merge_sort_random_order();
    test_merge_sort_with_duplicates();
    test_merge_sort_chars();

    // Test Quick Sort
    test_quick_sort_empty_array();
    test_quick_sort_single_element();
    test_quick_sort_already_sorted();
    test_quick_sort_reverse_sorted();
    test_quick_sort_random_order();
    test_quick_sort_with_duplicates();
    test_quick_sort_chars();

    // Test comparativi e edge cases
    test_both_sorts_produce_same_result();
    test_large_array();
    
    // Test funzioni di supporto
    test_swap_function();
    test_swap_chars();

    printf("\n=== All tests passed! ===\n");
    return 0;
}