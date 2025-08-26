#include "edit_distance.h"

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

int edit_distance_dyn_helper(const char *s1, const char *s2, int i, int j, int **dp) {
    if (i == 0) return j;  // s1 ended
    if (j == 0) return i;  // s2 ended
    
    if (dp[i][j] != -1) return dp[i][j];
    
    int result;
    if (s1[0] == s2[0]) {
        result = edit_distance_dyn_helper(s1 + 1, s2 + 1, i - 1, j - 1, dp);
    } else {
        int d_canc = 1 + edit_distance_dyn_helper(s1, s2 + 1, i, j - 1, dp);
        int d_ins = 1 + edit_distance_dyn_helper(s1 + 1, s2, i - 1, j, dp);
        result = min2(d_canc, d_ins);
    }
    
    dp[i][j] = result;
    return result;
}

int edit_distance_dyn(const char *s1, const char *s2) {
    if (s1 == NULL || s2 == NULL) return -1;
    
    int len1 = strlen(s1);
    int len2 = strlen(s2);
    
    // allocate and initiate dyn prog matrix
    int **dp = malloc((len1 + 1) * sizeof(int *));
    for (int i = 0; i <= len1; i++) {
        dp[i] = malloc((len2 + 1) * sizeof(int));
        for (int j = 0; j <= len2; j++) {
            dp[i][j] = -1;
        }
    }
    
    int result = edit_distance_dyn_helper(s1, s2, len1, len2, dp);
    
    for (int i = 0; i <= len1; i++) free(dp[i]);
    free(dp);
    
    return result;
}

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

int min2(int a, int b) {
    if(b < a){
        return b;
    }
    return a;
}