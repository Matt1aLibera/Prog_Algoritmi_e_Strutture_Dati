#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define INITIAL_CAPACITY 16
#define BUFFER_SIZE 1024

typedef struct{
    int id; 
    char* field1; 
    int field2; 
    double field3; 
} DataRecord; 

void sort_records(FILE *infile, FILE *outfile, size_t field, size_t algo); 
// Funzione di lettura record
DataRecord* read_data_records(FILE *input_file, unsigned long *record_count);

// Funzione di liberazione memoria
void free_data_records(DataRecord *records, unsigned long record_count);

// Funzioni di comparazione
int compare_int_field(const void *a, const void *b);
int compare_double_field(const void *a, const void *b);
int compare_string_field(const void *a, const void *b);

// Funzione di ordinamento principale
void sorting_controller(void *array, size_t element_count, size_t element_size, size_t algorithm, int (*comparator)(const void*, const void*));

static char *my_strdup(const char *s);