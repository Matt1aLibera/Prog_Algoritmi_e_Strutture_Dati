#include "main_ex2.h"

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
        output = fopen(output_path, "a"); 
    } else {
        output = fopen(output_path, "w"); 
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

void find_min_words(FILE *dictionary, FILE *correctme, FILE *output) {
    char input[WORD_LEN];
    int act;
    
    // load dictionary in memory
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

    while (fgets(input, sizeof(input), correctme) != NULL) {
        char *tok = strtok(input, ",.\t \n");
        while (tok != NULL) {
            tok[0] = tolower(tok[0]);
            
            Suggestions suggestions;
            suggestions.count = 0;
            suggestions.min_distance = INT_MAX;

            for (int i = 0; i < dict_size; i++) {
                act = edit_distance_dyn(tok, dict_words[i]);
                
                if (act < suggestions.min_distance) {
                    // new minimum distance found, array reset
                    suggestions.min_distance = act;
                    suggestions.count = 0;
                    strncpy(suggestions.words[suggestions.count], dict_words[i], WORD_LEN - 1);
                    suggestions.words[suggestions.count][WORD_LEN - 1] = '\0';
                    suggestions.count++;
                } 
                else if (act == suggestions.min_distance && suggestions.count < MAX_SUGGESTIONS) {
                    // adds new found min distance word to the array
                    strncpy(suggestions.words[suggestions.count], dict_words[i], WORD_LEN - 1);
                    suggestions.words[suggestions.count][WORD_LEN - 1] = '\0';
                    suggestions.count++;
                }
            }

            print_suggestions(output, tok, &suggestions);
            tok = strtok(NULL, ",.\t \n");
        }
    }
    
    // free memory
    for (int i = 0; i < dict_size; i++) {
        free(dict_words[i]);
    }
    free(dict_words);
}

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