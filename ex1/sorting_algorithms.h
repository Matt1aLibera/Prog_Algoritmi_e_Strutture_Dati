#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void merge_sort(void *base, size_t nitems, size_t size, int (*compare)(const void*, const void*)); 

void merge(void *base, size_t nitems_left, size_t nitems_right, size_t size, int (*compare)(const void*, const void*));

void quick_sort(void *base, size_t nitems, size_t size, int (*compare)(const void*, const void*));

size_t partition(void *base, size_t low, size_t high, size_t size, int (*compare)(const void*, const void*)); 

size_t partition_median_of_three(void *base, size_t start_index, size_t end_index, size_t size, int (*compare)(const void*, const void*));

void swap(void *a, void *b, size_t size); 