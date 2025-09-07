/**
 * @file edit_distance.h
 * @brief Edit Distance algorithms implementation
 * 
 * This header provides functions for calculating the Levenshtein edit distance
 * between two strings using both recursive and dynamic programming approaches.
 * The edit distance is the minimum number of operations (insertions, deletions,
 * substitutions) required to transform one string into another.
 */

#ifndef EDIT_DISTANCE_H
#define EDIT_DISTANCE_H

#include <string.h>
#include <stdlib.h>
#include <limits.h>

/**
 * @brief Calculates edit distance using recursive approach
 * 
 * Computes the Levenshtein distance between two strings recursively.
 * This approach has exponential time complexity O(3^(m+n)) and is
 * only suitable for very short strings.
 * 
 * @param s1 First input string (must not be NULL)
 * @param s2 Second input string (must not be NULL)
 * @return int Edit distance between strings, or -1 if either string is NULL
 */
int edit_distance(const char *s1, const char *s2);

/**
 * @brief Helper function for dynamic programming edit distance
 * 
 * Recursive helper function with memoization for the dynamic programming
 * solution. This function should not be called directly; use edit_distance_dyn() instead.
 * 
 * @param s1 First input string
 * @param s2 Second input string
 * @param i Current length of first string being considered
 * @param j Current length of second string being considered
 * @param dp Dynamic programming memoization table
 * @return int Edit distance for the current substring
 */
int edit_distance_dyn_helper(const char *s1, const char *s2, int i, int j, int **dp);

/**
 * @brief Calculates edit distance using dynamic programming
 * 
 * Computes the Levenshtein distance between two strings using dynamic
 * programming with memoization. This approach has time complexity O(m*n)
 * and space complexity O(m*n), making it suitable for longer strings.
 * 
 * @param s1 First input string (must not be NULL)
 * @param s2 Second input string (must not be NULL)
 * @return int Edit distance between strings, or -1 if either string is NULL
 */
int edit_distance_dyn(const char *s1, const char *s2);

/**
 * @brief Returns the minimum of three integers
 * 
 * Utility function that finds the smallest value among three integers.
 * 
 * @param a First integer
 * @param b Second integer
 * @param c Third integer
 * @return int The smallest value among a, b, and c
 */
int min3(int a, int b, int c);

#endif /* EDIT_DISTANCE_H */