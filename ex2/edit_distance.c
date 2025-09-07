/**
 * @file edit_distance.c
 * @brief Implementation of edit distance algorithms
 * 
 * Contains the actual implementation of recursive and dynamic programming
 * approaches for calculating the Levenshtein edit distance between strings.
 */

#include "edit_distance.h"

/**
 * @brief Recursive edit distance calculation
 * 
 * Implements the naive recursive approach to calculate Levenshtein distance.
 * Time complexity: O(3^(m+n)) where m and n are string lengths.
 * Space complexity: O(m+n) due to recursion stack.
 * 
 * @param s1 First input string
 * @param s2 Second input string
 * @return int Edit distance or -1 for invalid input
 */
int edit_distance(const char *s1, const char *s2){
    if (s1 == NULL || s2 == NULL){ 
        return -1;
    }
    if (*s1 == '\0') return strlen(s2);
    if (*s2 == '\0') return strlen(s1);
    
    int d_noop = INT_MAX;
    
    if (*s1 == *s2)
        d_noop = edit_distance(s1 + 1, s2 + 1);
    
    int d_canc = 1 + edit_distance(s1, s2 + 1);
    int d_ins = 1 + edit_distance(s1 + 1, s2);
    
    return min3(d_noop, d_canc, d_ins);
}

/**
 * @brief Dynamic programming helper with memoization
 * 
 * Recursive function that uses memoization to avoid redundant calculations.
 * Fills the DP table with edit distances for all substring combinations.
 * 
 * @param s1 First input string
 * @param s2 Second input string
 * @param i Current length of first string substring
 * @param j Current length of second string substring
 * @param dp Dynamic programming memoization table
 * @return int Edit distance for substrings s1[0..i-1] and s2[0..j-1]
 */
int edit_distance_dyn_helper(const char *s1, const char *s2, int i, int j, int **dp) {
    if (i == 0) return j;  // s1 ended - insert all remaining chars of s2
    if (j == 0) return i;  // s2 ended - delete all remaining chars of s1
    
    if (dp[i][j] != -1) return dp[i][j];
    
    int d_noop = INT_MAX;
    int result;

    if (s1[0] == s2[0]) {
        // Characters match - no operation needed
        result = edit_distance_dyn_helper(s1 + 1, s2 + 1, i - 1, j - 1, dp);
    } else {
        // Characters differ - consider all operations
        int d_canc = 1 + edit_distance_dyn_helper(s1, s2 + 1, i, j - 1, dp);     // Insert in s1
        int d_ins = 1 + edit_distance_dyn_helper(s1 + 1, s2, i - 1, j, dp);      // Delete from s1
        result = min3(d_noop, d_canc, d_ins);                                    // Substitution
    }
    dp[i][j] = result;
    return result;
}

/**
 * @brief Dynamic programming edit distance calculation
 * 
 * Implements the efficient dynamic programming approach with memoization.
 * Time complexity: O(m*n) where m and n are string lengths.
 * Space complexity: O(m*n) for the DP table.
 * 
 * @param s1 First input string
 * @param s2 Second input string
 * @return int Edit distance or -1 for invalid input
 */
int edit_distance_dyn(const char *s1, const char *s2) {
    if (s1 == NULL || s2 == NULL) return -1;
    
    int len1 = strlen(s1);
    int len2 = strlen(s2);
    
    // Allocate and initialize dynamic programming matrix
    int **dp = malloc((len1 + 1) * sizeof(int *));
    for (int i = 0; i <= len1; i++) {
        dp[i] = malloc((len2 + 1) * sizeof(int));
        for (int j = 0; j <= len2; j++) {
            dp[i][j] = -1;  // Initialize with -1 (uncomputed)
        }
    }
    
    int result = edit_distance_dyn_helper(s1, s2, len1, len2, dp);
    
    // Free allocated memory
    for (int i = 0; i <= len1; i++) free(dp[i]);
    free(dp);
    
    return result;
}

/**
 * @brief Finds minimum of three integers
 * 
 * Utility function that returns the smallest value among three integers.
 * Used to determine the minimum cost operation in edit distance calculation.
 * 
 * @param a First integer value
 * @param b Second integer value
 * @param c Third integer value
 * @return int Minimum value among the three inputs
 */
int min3(int a, int b, int c) {
    int min = a;
    if (b < min){
        min = b;
    }
    if (c < min){
        min = c;
    }
    return min;
}