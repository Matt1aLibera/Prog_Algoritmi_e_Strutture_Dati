/**
 * @file sorting_algorithms.h
 * @brief Sorting algorithms implementation (Merge Sort and Quick Sort)
 * 
 * This header provides declarations for various sorting algorithms that work
 * on generic data types using function pointers for comparison.
 */

#ifndef SORTING_ALGORITHMS_H
#define SORTING_ALGORITHMS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/**
 * @brief Sorts an array using the Merge Sort algorithm
 * 
 * @param base Pointer to the first element of the array
 * @param nitems Number of elements in the array
 * @param size Size of each element in bytes
 * @param compare Function pointer to comparison function
 */
void merge_sort(void *base, size_t nitems, size_t size, int (*compare)(const void*, const void*));

/**
 * @brief Merges two sorted subarrays into a single sorted array
 * 
 * @param base Pointer to the first element of the array
 * @param nitems_left Number of elements in the left subarray
 * @param nitems_right Number of elements in the right subarray
 * @param size Size of each element in bytes
 * @param compare Function pointer to comparison function
 */
void merge(void *base, size_t nitems_left, size_t nitems_right, size_t size, int (*compare)(const void*, const void*));

/**
 * @brief Sorts an array using the Quick Sort algorithm (iterative version)
 * 
 * Uses an iterative approach with a stack to avoid recursion and prevent
 * stack overflow with large arrays.
 * 
 * @param base Pointer to the first element of the array
 * @param nitems Number of elements in the array
 * @param size Size of each element in bytes
 * @param compare Function pointer to comparison function
 */
void quick_sort(void *base, size_t nitems, size_t size, int (*compare)(const void*, const void*));

/**
 * @brief Partitions an array for Quick Sort using last element as pivot
 * 
 * @param base Pointer to the first element of the array
 * @param low Starting index of the subarray to partition
 * @param high Ending index of the subarray to partition
 * @param size Size of each element in bytes
 * @param compare Function pointer to comparison function
 * @return size_t Index of the pivot element after partitioning
 */
size_t partition(void *base, size_t low, size_t high, size_t size, int (*compare)(const void*, const void*));

/**
 * @brief Partitions an array using median-of-three pivot selection
 * 
 * Selects the median of first, middle, and last elements as pivot
 * to improve performance on already sorted or reverse-sorted arrays.
 * 
 * @param base Pointer to the first element of the array
 * @param start_index Starting index of the subarray to partition
 * @param end_index Ending index of the subarray to partition
 * @param size Size of each element in bytes
 * @param compare Function pointer to comparison function
 * @return size_t Index of the pivot element after partitioning
 */
size_t partition_median_of_three(void *base, size_t start_index, size_t end_index, size_t size, int (*compare)(const void*, const void*));

/**
 * @brief Swaps two elements of any type
 * 
 * @param element_a Pointer to the first element
 * @param element_b Pointer to the second element
 * @param size Size of each element in bytes
 */
void swap(void *element_a, void *element_b, size_t size);

#endif /* SORTING_ALGORITHMS_H */