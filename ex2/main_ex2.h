#ifndef MAIN_EX2_H
#define MAIN_EX2_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h> 
#include <limits.h>
#include <time.h>
#include "edit_distance.h"

#define WORD_LEN 1024
#define MAX_SUGGESTIONS 1

typedef struct {
    char words[MAX_SUGGESTIONS][WORD_LEN]; //array of suggested words
    int count;                             //actual number of suggestion
    int min_distance;                      //min edit distance found
} Suggestions;

void find_min_words(FILE *dictionary, FILE *correctme, FILE *output);
void print_suggestions(FILE *output, const char *word, Suggestions *suggestions);

#endif