/**
 * @file main_ex1.h
 * @brief Main header for sorting application with DataRecord structure
 * 
 * This header defines the DataRecord structure and function prototypes
 * for reading, sorting, and writing data records from/to CSV files.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define INITIAL_CAPACITY 16    /**< Initial capacity for record array */
#define BUFFER_SIZE 1024       /**< Buffer size for reading lines from file */

/**
 * @brief Data structure representing a record with multiple fields
 * 
 * This structure holds data read from CSV files with integer, string,
 * and floating-point fields.
 */
typedef struct {
    int id;                    /**< Unique identifier for the record */
    char* field1;              /**< String field data */
    int field2;                /**< Integer field data */
    double field3;             /**< Floating-point field data */
} DataRecord;

/**
 * @brief Main sorting function for records
 * 
 * Reads records from input file, sorts them based on specified field
 * and algorithm, and writes sorted records to output file.
 * 
 * @param infile Input file pointer
 * @param outfile Output file pointer
 * @param field Field to sort by (1=string, 2=integer, 3=double)
 * @param algo Algorithm to use (1=MergeSort, 2=QuickSort)
 */
void sort_records(FILE *infile, FILE *outfile, size_t field, size_t algo);

/**
 * @brief Reads data records from file into dynamically allocated array
 * 
 * @param input_file File pointer to read from
 * @param record_count Pointer to variable that will receive record count
 * @return DataRecord* Dynamically allocated array of records
 */
DataRecord* read_data_records(FILE *input_file, unsigned long *record_count);

/**
 * @brief Frees memory allocated for data records
 * 
 * @param records Array of records to free
 * @param record_count Number of records in the array
 */
void free_data_records(DataRecord *records, unsigned long record_count);

/**
 * @brief Comparator function for integer field
 * 
 * @param a Pointer to first DataRecord
 * @param b Pointer to second DataRecord
 * @return int Negative if a < b, zero if equal, positive if a > b
 */
int compare_int_field(const void *a, const void *b);

/**
 * @brief Comparator function for double field
 * 
 * Uses epsilon comparison for floating-point precision handling
 * 
 * @param a Pointer to first DataRecord
 * @param b Pointer to second DataRecord
 * @return int Negative if a < b, zero if equal, positive if a > b
 */
int compare_double_field(const void *a, const void *b);

/**
 * @brief Comparator function for string field
 * 
 * Handles NULL strings safely
 * 
 * @param a Pointer to first DataRecord
 * @param b Pointer to second DataRecord
 * @return int Negative if a < b, zero if equal, positive if a > b
 */
int compare_string_field(const void *a, const void *b);

/**
 * @brief Controller function for sorting algorithms
 * 
 * Measures and reports execution time for the chosen algorithm
 * 
 * @param array Array to sort
 * @param element_count Number of elements in array
 * @param element_size Size of each element in bytes
 * @param algorithm Algorithm to use (1=MergeSort, 2=QuickSort)
 * @param comparator Comparator function for sorting
 */
void sorting_controller(void *array, size_t element_count, size_t element_size, 
                       size_t algorithm, int (*comparator)(const void*, const void*));

/**
 * @brief Safe string duplication function
 * 
 * Private function for internal use - creates a duplicate of a string
 * 
 * @param s String to duplicate
 * @return char* Duplicated string, or NULL if allocation fails
 */
static char *my_strdup(const char *s);