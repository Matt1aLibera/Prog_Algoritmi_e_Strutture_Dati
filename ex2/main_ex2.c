/**
 * @file main_ex2.c
 * @brief Main implementation of spell checker application
 * 
 * This file contains the main function and implementation of a spell checker
 * that uses edit distance algorithms to find corrections for misspelled words.
 * The application processes text files and provides suggestions from a dictionary.
 */

#include "main_ex2.h"

/**
 * @brief Main entry point of the spell checker application
 * 
 * Handles command line arguments, file operations, and coordinates the
 * spell checking process. Measures and reports execution time.
 * 
 * Usage: ./main_ex2 <dictionary> <correctme> [output]
 * Example: "./bin/main_ex2 data/dictionary.txt data/correctme.txt"
 * 
 * @param argc Number of command line arguments
 * @param argv Array of command line arguments
 * @return int Exit status (0 for success, non-zero for failure)
 */
int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <dictionary> <correctme> [output]\n", argv[0]);
        fprintf(stderr, "One or more parameters are missing\n");
        exit(EXIT_FAILURE);
    }
    
    const char *output_path = (argc > 3) ? argv[3] : "./data/output.txt";
    
    printf("Attempting to open files:\n");
    printf("Dictionary: %s\n", argv[1]);
    printf("Correctme: %s\n", argv[2]);
    printf("Output: %s\n", output_path);

    FILE *dictionary = fopen(argv[1], "r");
    FILE *correctme = fopen(argv[2], "r");

    if (dictionary == NULL || correctme == NULL) {
        fprintf(stderr, "Error opening input files\n");
        if (dictionary) fclose(dictionary);
        if (correctme) fclose(correctme);
        exit(EXIT_FAILURE);
    }

    FILE *output;
    int opened = access(output_path, F_OK);  
    if (opened == 0) {
        output = fopen(output_path, "a"); // Append if file exists
    } else {
        output = fopen(output_path, "w"); // Create new if file doesn't exist
    }
    
    if (output == NULL) {
        fprintf(stderr, "Error opening output file\n");
        fclose(dictionary);
        fclose(correctme);
        exit(EXIT_FAILURE);
    }

    clock_t begin = clock();
    find_min_words(dictionary, correctme, output);
    clock_t end = clock();
    
    double total_time = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Total time: %f seconds\n", total_time);

    fclose(dictionary);
    fclose(correctme);
    fclose(output);

    return 0;
}

/**
 * @brief Processes text file and finds spelling suggestions
 * 
 * Loads dictionary into memory, processes the input text file token by token,
 * and uses edit distance to find the closest matching words from the dictionary.
 * 
 * @param dictionary File pointer to dictionary word list
 * @param correctme File pointer to text file to spell check
 * @param output File pointer for output results
 */
void find_min_words(FILE *dictionary, FILE *correctme, FILE *output) {
    char input[WORD_LEN];
    int act;
    
    // Load dictionary into memory for efficient access
    char **dict_words = NULL;
    int dict_size = 0;
    char word[WORD_LEN];
    
    rewind(dictionary);
    while (fscanf(dictionary, "%1023s", word) != EOF) {
        dict_words = realloc(dict_words, (dict_size + 1) * sizeof(char *));
        dict_words[dict_size] = malloc(strlen(word) + 1);
        strcpy(dict_words[dict_size], word);
        dict_size++;
    }
    printf("Loaded %d words from dictionary\n", dict_size);

    // Process each line of the input file
    while (fgets(input, sizeof(input), correctme) != NULL) {
        char *tok = strtok(input, ",.\t \n");
        while (tok != NULL) {
            // Convert first character to lowercase for case-insensitive comparison
            tok[0] = tolower(tok[0]);
            
            Suggestions suggestions;
            suggestions.count = 0;
            suggestions.min_distance = INT_MAX;

            // Compare current word against all dictionary words
            for (int i = 0; i < dict_size; i++) {
                act = edit_distance_dyn(tok, dict_words[i]);
                
                if (act < suggestions.min_distance) {
                    // New minimum distance found, reset suggestions array
                    suggestions.min_distance = act;
                    suggestions.count = 0;
                    strncpy(suggestions.words[suggestions.count], dict_words[i], WORD_LEN - 1);
                    suggestions.words[suggestions.count][WORD_LEN - 1] = '\0';
                    suggestions.count++;
                } 
                else if (act == suggestions.min_distance && suggestions.count < MAX_SUGGESTIONS) {
                    // Add new word with same minimum distance to suggestions
                    strncpy(suggestions.words[suggestions.count], dict_words[i], WORD_LEN - 1);
                    suggestions.words[suggestions.count][WORD_LEN - 1] = '\0';
                    suggestions.count++;
                }
            }

            print_suggestions(output, tok, &suggestions);
            tok = strtok(NULL, ",.\t \n");
        }
    }
    
    // Free allocated memory for dictionary
    for (int i = 0; i < dict_size; i++) {
        free(dict_words[i]);
    }
    free(dict_words);
}

/**
 * @brief Formats and writes suggestions to output file
 * 
 * Creates a formatted output showing the original word, minimum edit distance,
 * and suggested corrections (if any).
 * 
 * @param output File pointer for output
 * @param word The original word that was checked
 * @param suggestions Structure containing correction suggestions
 */
void print_suggestions(FILE *output, const char *word, Suggestions *suggestions) {
    fprintf(output, "Word: %s\n", word);
    fprintf(output, "Min_distance: %d\n", suggestions->min_distance);
    
    if (suggestions->min_distance == 0) {
        fprintf(output, "✓ Correct word\n");
    } else {
        fprintf(output, "Suggestions (%d):\n", suggestions->count);
        for (int i = 0; i < suggestions->count; i++) {
            fprintf(output, "  - %s\n", suggestions->words[i]);
        }
    }
    fprintf(output, "\n");
}