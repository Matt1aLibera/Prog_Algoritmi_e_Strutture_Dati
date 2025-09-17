/**
 * @file main_ex2.h
 * @brief Spell checker application using edit distance algorithm
 * 
 * This header defines the main structures and functions for a spell checker
 * application that uses the Levenshtein edit distance to find suggestions
 * for misspelled words in a text file based on a dictionary.
 */

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

#define WORD_LEN 1024        /**< Maximum length for a word */
#define MAX_SUGGESTIONS 10    /**< Maximum number of suggestions to provide per word */

/**
 * @brief Structure to hold spelling suggestions for a word
 * 
 * Contains an array of suggested corrections and metadata about
 * the suggestions including the minimum edit distance found.
 */
typedef struct {
    char words[MAX_SUGGESTIONS][WORD_LEN]; /**< Array of suggested words */
    int count;                             /**< Actual number of suggestions found */
    int min_distance;                      /**< Minimum edit distance found */
} Suggestions;

/**
 * @brief Finds spelling suggestions for words in a text file
 * 
 * Processes a text file word by word, compares each word against a dictionary
 * using edit distance, and finds the closest matching words.
 * 
 * @param dictionary File pointer to the dictionary word list
 * @param correctme File pointer to the text file to check
 * @param output File pointer for output results
 */
void find_min_words(FILE *dictionary, FILE *correctme, FILE *output);

/**
 * @brief Prints spelling suggestions to output file
 * 
 * Formats and writes the suggestions for a single word to the output file
 * in a human-readable format.
 * 
 * @param output File pointer for output
 * @param word The original word that was checked
 * @param suggestions Suggestions structure containing correction options
 */
void print_suggestions(FILE *output, const char *word, Suggestions *suggestions);

#endif /* MAIN_EX2_H */