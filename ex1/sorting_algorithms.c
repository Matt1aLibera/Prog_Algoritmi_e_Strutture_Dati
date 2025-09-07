#include "sorting_algorithms.h"

void merge_sort(void *base, size_t nitems, size_t size, int (*compare)(const void*, const void*)) {
    if (nitems <= 1){
        return;
    }
        size_t nitems_left = nitems / 2; 
        size_t nitems_right = nitems - nitems_left;
        merge_sort(base, nitems_left, size, compare); 
        merge_sort((char *)base + nitems_left * size, nitems_right, size, compare); 
        merge(base, nitems_left, nitems_right, size, compare); 
}

void merge(void *base, size_t nitems_left, size_t nitems_right, size_t size, int (*compare)(const void*, const void*)) {
    size_t nitems_merged = nitems_left + nitems_right; 
    void *merge_buffer = malloc(nitems_merged * size); 
    if (merge_buffer == NULL) {
        fprintf(stderr, "Error: Failed to allocate %zu bytes for merge buffer\n", nitems_merged * size);
        exit(EXIT_FAILURE);
    }

    size_t left_index = 0, right_index = 0, buffer_index = 0; 

    char *left_array = (char *)base; 
    char *right_array = (char *)base + nitems_left * size; 

    while (left_index < nitems_left && right_index < nitems_right) {
        if (compare(left_array + left_index * size, right_array + right_index * size) <= 0) {
            memcpy(merge_buffer + buffer_index * size, left_array + left_index * size, size); 
            left_index++; 
        } else {
            memcpy(merge_buffer + buffer_index * size, right_array + right_index * size, size); 
            right_index++; 
        }
        buffer_index++; 
    }

    if (left_index < nitems_left) {
        size_t remaining_left = nitems_left - left_index;
        memcpy(merge_buffer + buffer_index * size, 
               left_array + left_index * size, 
               remaining_left * size);
        buffer_index += remaining_left;
    }

    if (right_index < nitems_right) {
        size_t remaining_right = nitems_right - right_index;
        memcpy(merge_buffer + buffer_index * size, 
               right_array + right_index * size, 
               remaining_right * size);
    }
    
    memcpy(base, merge_buffer, nitems_merged * size); 
    free(merge_buffer); 
}

void quick_sort(void *base, size_t nitems, size_t size, int (*compar)(const void*, const void*)) {
    if (nitems <= 1) return;
    
    // Stack to menage subarray intervals [low, high), big enough to handle the worst case (nitems*2, all data already sorted)
    size_t *index_stack = malloc(nitems * sizeof(size_t) * 2);
    if (!index_stack) {
        fprintf(stderr, "Memory allocation failed for quicksort stack\n");
        exit(EXIT_FAILURE);
    }
    
    int stack_top = -1;
    index_stack[++stack_top] = 0;          // Push start index of first subarray
    index_stack[++stack_top] = nitems;     // Push end index of first subarray
    
    while (stack_top >= 0) {
        size_t subarray_end = index_stack[stack_top--];    // Pop end index
        size_t subarray_start = index_stack[stack_top--];  // Pop start index
        
        if (subarray_end - subarray_start > 1) {
            // Partition the subarray and get pivot position
            size_t pivot_index = partition(base, subarray_start, subarray_end, size, compar);
            
            // Push left subarray to stack if it has more than 1 element
            if (pivot_index - subarray_start > 1) {
                index_stack[++stack_top] = subarray_start;
                index_stack[++stack_top] = pivot_index;
            }
            
            // Push right subarray to stack if it has more than 1 element
            if (subarray_end - pivot_index > 1) {
                index_stack[++stack_top] = pivot_index + 1;
                index_stack[++stack_top] = subarray_end;
            }
        }
    }
    
    free(index_stack);
}

size_t partition(void *base, size_t start_index, size_t end_index, size_t size, int (*compare)(const void*, const void*)) {
    
    char *array_base = (char *)base;
    void *pivot_element = array_base + (end_index - 1) * size;  // Use last element as pivot
    size_t partition_index = start_index - 1;  // Index of smaller element
    
    // Iterate through the subarray
    for (size_t current_index = start_index; current_index < end_index; current_index++) {
        // If current element is smaller than pivot
        if (compare(array_base + current_index * size, pivot_element) < 0) {
            partition_index++;
            swap(array_base + partition_index * size, array_base + current_index * size, size);
        }
    }
    
    // Place pivot in correct position
    swap(array_base + (partition_index + 1) * size, array_base + (end_index - 1) * size, size);
    
    return partition_index + 1;
}

size_t partition_median_of_three(void *base, size_t start_index, size_t end_index, size_t size, int (*compare)(const void*, const void*)) {
    
    char *array_base = (char *)base;
    
    // MEDIAN OF THREE - Select best pivot from first, middle, and last elements
    size_t mid = start_index + (end_index - start_index) / 2;
    
    // Sort the three elements to find the median
    if (compare(array_base + start_index * size, array_base + mid * size) > 0) {
        swap(array_base + start_index * size, array_base + mid * size, size);
    }
    if (compare(array_base + start_index * size, array_base + (end_index - 1) * size) > 0) {
        swap(array_base + start_index * size, array_base + (end_index - 1) * size, size);
    }
    if (compare(array_base + mid * size, array_base + (end_index - 1) * size) > 0) {
        swap(array_base + mid * size, array_base + (end_index - 1) * size, size);
    }
    
    // Use median (middle element) as pivot
    void *pivot_element = array_base + mid * size;
    
    // Temporarily move pivot to the end for consistent partitioning
    swap(pivot_element, array_base + (end_index - 1) * size, size);
    pivot_element = array_base + (end_index - 1) * size;
    
    size_t partition_index = start_index - 1;
    
    // Iterate through subarray (excluding pivot at the end)
    for (size_t current_index = start_index; current_index < end_index - 1; current_index++) {
        if (compare(array_base + current_index * size, pivot_element) < 0) {
            partition_index++;
            swap(array_base + partition_index * size, array_base + current_index * size, size);
        }
    }
    
    // Move pivot to its final sorted position
    swap(array_base + (partition_index + 1) * size, pivot_element, size);
    
    return partition_index + 1;
}

void swap(void *element_a, void *element_b, size_t size) {
    // Allocate temporary buffer for swapping
    char *temp_buffer = malloc(size);
    if (temp_buffer == NULL) {
        fprintf(stderr, "Memory allocation failed in swap function\n");
        exit(EXIT_FAILURE);
    }
   
    // Perform the swap using memcpy
    memcpy(temp_buffer, element_a, size);
    memcpy(element_a, element_b, size);
    memcpy(element_b, temp_buffer, size);
    
    free(temp_buffer);
}