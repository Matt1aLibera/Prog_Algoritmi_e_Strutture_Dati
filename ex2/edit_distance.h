#include <string.h>
#include <stdlib.h>
#include <limits.h>

int edit_distance(const char *s1, const char *s2);

int edit_distance_dyn_helper(const char *s1, const char *s2, int i, int j, int **dp);

int edit_distance_dyn(const char *s1, const char *s2);

int min3(int a, int b, int c);

int min2(int a, int b);