/**
 * @file main_ex1.c
 * @brief Main application for sorting CSV records
 * 
 * This application reads CSV files containing data records, sorts them
 * using either MergeSort or QuickSort algorithm on specified fields,
 * and writes the sorted results to output files.
 */
#include "main_ex1.h"
#include "sorting_algorithms.h"

/**
 * @brief Main entry point of the application
 * 
 * Parses command line arguments, validates parameters, opens files,
 * and initiates the sorting process.
 * 
 * Usage: ./main_ex1 <input_file> <output_file> <field> <algorithm>
 * Example: "./bin/main_ex1 csv/records.csv csv/sorted.csv 1 1"
 * 
 * @param argc Argument count
 * @param argv Argument vector
 * @return int Exit status (EXIT_SUCCESS or EXIT_FAILURE)
 */
int main(int argc, char *argv[]) {
    // Check for correct number of parameters
    if (argc != 5) {
        fprintf(stderr, "Error: Expected 4 parameters but got %d\n", argc - 1);
        fprintf(stderr, "Usage: %s <input_file> <output_file> <field> <algorithm>\n", argv[0]);
        fprintf(stderr, "  field: 1 (string), 2 (integer), 3 (floating point)\n");
        fprintf(stderr, "  algorithm: 1 (MergeSort), 2 (QuickSort)\n");
        exit(EXIT_FAILURE);
    }

    const char *file_name = argv[1]; 
    const char *output_file = argv[2]; 
    size_t field = (size_t)atoi(argv[3]);
    size_t algo = (size_t)atoi(argv[4]);
    
    // Validate algorithm parameter
    if (algo != 1 && algo != 2) {
        fprintf(stderr, "Error: Algorithm must be 1 (MergeSort) or 2 (QuickSort), got %ld\n", algo);
        exit(EXIT_FAILURE);
    }

    // Validate field parameter
    if (field < 1 || field > 3) {
        fprintf(stderr, "Error: Field must be 1, 2 or 3, got %ld\n", field);
        exit(EXIT_FAILURE);
    }

    // Open input file
    FILE *infile = fopen(file_name, "r");
    if (!infile) {
        fprintf(stderr, "Error: Cannot open input file '%s'\n", file_name);
        perror("Details");
        exit(EXIT_FAILURE);
    }
 
    // Open output file
    FILE *outfile = fopen(output_file, "w"); 
    if (!outfile) {
        fprintf(stderr, "Error: Cannot create/open output file '%s'\n", output_file);
        perror("Details");
        fclose(infile);
        exit(EXIT_FAILURE);
    }

    // Execute sorting
    sort_records(infile, outfile, field, algo);

    // Cleanup
    fclose(infile);
    fclose(outfile);

    return EXIT_SUCCESS;
}

/**
 * @brief Main sorting workflow function
 * 
 * Reads records, selects appropriate comparator, sorts records,
 * and writes sorted output to file.
 * 
 * @param infile Input file pointer
 * @param outfile Output file pointer
 * @param field Field to sort by (1=string, 2=integer, 3=double)
 * @param algo Algorithm to use (1=MergeSort, 2=QuickSort)
 */
void sort_records(FILE *infile, FILE *outfile, size_t field, size_t algo) {
    unsigned long record_count = INITIAL_CAPACITY;
    DataRecord *data_records = read_data_records(infile, &record_count);

    if (record_count == 0) {
        fprintf(stderr, "Error: No records found in input file\n");
        fclose(outfile);
        exit(EXIT_FAILURE);
    }

    // Select appropriate comparator based on field
    switch(field) {
        case 1:
            sorting_controller(data_records, record_count, sizeof(DataRecord), algo, compare_string_field);
            break;
        case 2:
            sorting_controller(data_records, record_count, sizeof(DataRecord), algo, compare_int_field);
            break;
        case 3:
            sorting_controller(data_records, record_count, sizeof(DataRecord), algo, compare_double_field);
            break;
        default:
            fprintf(stderr, "Error: Invalid field parameter %ld. Must be 1, 2 or 3\n", field);
            fclose(outfile);
            free_data_records(data_records, record_count);
            exit(EXIT_FAILURE);
    }

    // Write sorted records to output file
    for (unsigned long i = 0; i < record_count; i++) {
        fprintf(outfile, "%d,%s,%d,%.6f\n", 
                data_records[i].id, 
                data_records[i].field1, 
                data_records[i].field2, 
                data_records[i].field3);
    }

    free_data_records(data_records, record_count);
}

/**
 * @brief Controls sorting execution and measures performance
 * 
 * @param array Array to sort
 * @param element_count Number of elements in array
 * @param element_size Size of each element in bytes
 * @param algorithm Algorithm to use (1=MergeSort, 2=QuickSort)
 * @param comparator Comparator function for sorting
 */
void sorting_controller(void *array, size_t element_count, size_t element_size, 
                       size_t algorithm, int (*comparator)(const void*, const void*)) {
    
    clock_t start_time = clock();
    
    if (algorithm == 1) {
        merge_sort(array, element_count, element_size, comparator);
    } else if (algorithm == 2) {
        quick_sort(array, element_count, element_size, comparator);
    }
    
    clock_t end_time = clock(); 

    double execution_time = (double)(end_time - start_time) / CLOCKS_PER_SEC; 
    
    const char *algorithm_name = (algorithm == 1) ? "MergeSort" : "QuickSort";   
    
    printf("Execution time: %s sorted %ld elements in %.6f seconds\n", 
           algorithm_name, element_count, execution_time); 
}

/**
 * @brief Frees memory allocated for data records
 * 
 * Safely handles NULL pointers and sets pointers to NULL after freeing
 * 
 * @param records Array of records to free
 * @param record_count Number of records in the array
 */
void free_data_records(DataRecord *records, unsigned long record_count) {
    if (records == NULL) return;

    for (unsigned long i = 0; i < record_count; i++) {
        if (records[i].field1 != NULL) {
            free(records[i].field1);
            records[i].field1 = NULL; // Set to NULL after freeing
        }
    }
    free(records); 
}

/**
 * @brief Comparator for integer field with overflow protection
 * 
 * @param a Pointer to first DataRecord
 * @param b Pointer to second DataRecord
 * @return int Negative if a < b, zero if equal, positive if a > b
 */
int compare_int_field(const void *a, const void *b) {
    
    const DataRecord *record_a = (const DataRecord*)a; 
    const DataRecord *record_b = (const DataRecord*)b; 

    // Avoid overflow for very large numbers
    if (record_a->field2 < record_b->field2) return -1;
    if (record_a->field2 > record_b->field2) return 1;
    return 0;
}

/**
 * @brief Comparator for string field with NULL safety
 * 
 * @param a Pointer to first DataRecord
 * @param b Pointer to second DataRecord
 * @return int Negative if a < b, zero if equal, positive if a > b
 */
int compare_string_field(const void *a, const void *b) {
    
    const DataRecord *record_a = (const DataRecord*)a; 
    const DataRecord *record_b = (const DataRecord*)b;

    // Safe handling of NULL strings
    if (record_a->field1 == NULL && record_b->field1 == NULL) return 0;
    if (record_a->field1 == NULL) return -1;
    if (record_b->field1 == NULL) return 1;

    return strcmp(record_a->field1, record_b->field1);
}

/**
 * @brief Comparator for double field with epsilon precision
 * 
 * Uses epsilon comparison to handle floating-point precision issues
 * 
 * @param a Pointer to first DataRecord
 * @param b Pointer to second DataRecord
 * @return int Negative if a < b, zero if equal, positive if a > b
 */
int compare_double_field(const void *a, const void *b) {
    
    const DataRecord *record_a = (const DataRecord*)a;  
    const DataRecord *record_b = (const DataRecord*)b;
    
    const double epsilon = 1e-10;
    double difference = record_a->field3 - record_b->field3;
    
    if (fabs(difference) < epsilon) {
        return 0; 
    }
    return (difference > 0) ? 1 : -1;
}

/**
 * @brief Reads CSV records from file into dynamic array
 * 
 * Handles memory allocation, parsing, and error checking
 * 
 * @param input_file File pointer to read from
 * @param record_count Pointer to variable that will receive record count
 * @return DataRecord* Dynamically allocated array of records
 */
DataRecord* read_data_records(FILE *input_file, unsigned long *record_count) {
    char line_buffer[BUFFER_SIZE];
    unsigned long current_capacity = *record_count;
    unsigned long records_read = 0;
    DataRecord *record_array = malloc(current_capacity * sizeof(DataRecord));

    if (record_array == NULL) {
        fprintf(stderr, "Memory allocation failed for record array\n");
        exit(EXIT_FAILURE);
    }

    // Initialize all records
    for (unsigned long i = 0; i < current_capacity; i++) {
        record_array[i].field1 = NULL;
        record_array[i].id = 0;
        record_array[i].field2 = 0;
        record_array[i].field3 = 0.0;
    }

    // Read and parse each line
    while (fgets(line_buffer, BUFFER_SIZE, input_file) != NULL) {
        // Remove newline character if present
        line_buffer[strcspn(line_buffer, "\n")] = '\0';
        
        // Resize array if needed
        if (records_read == current_capacity) {
            current_capacity = (current_capacity * 3) / 2 + 1; // 1.5x growth
            DataRecord *temp = realloc(record_array, current_capacity * sizeof(DataRecord));
            if (temp == NULL) {
                fprintf(stderr, "Memory reallocation failed during reading\n");
                free_data_records(record_array, records_read);
                exit(EXIT_FAILURE);
            }
            record_array = temp;

            // Initialize new elements
            for (unsigned long i = records_read; i < current_capacity; i++) {
                record_array[i].field1 = NULL;
                record_array[i].id = 0;
                record_array[i].field2 = 0;
                record_array[i].field3 = 0.0;
            }
        }

        // Parse CSV fields
        int id_value;
        int int_field;
        double double_field;
        char string_field[512]; // Temporary buffer for string field

        int parse_result = sscanf(line_buffer, "%d, %511[^,], %d, %lf", 
                                 &id_value, string_field, &int_field, &double_field);

        if (parse_result != 4) {
            fprintf(stderr, "Error: Failed to parse line %lu - invalid format\n", records_read + 1);
            // Initialize structure even if parsing fails
            record_array[records_read].field1 = NULL;
            record_array[records_read].id = 0;
            record_array[records_read].field2 = 0;
            record_array[records_read].field3 = 0.0;
            continue;
        }

        // Assign values to record
        record_array[records_read].id = id_value;
        record_array[records_read].field1 = my_strdup(string_field);
        record_array[records_read].field2 = int_field;
        record_array[records_read].field3 = double_field;

        if (record_array[records_read].field1 == NULL) {
            fprintf(stderr, "Error: Memory allocation failed for string field in line %lu\n", records_read + 1);
            free_data_records(record_array, records_read);
            exit(EXIT_FAILURE);
        }

        records_read++;
    }

    *record_count = records_read;
    return record_array;
}

/**
 * @brief Safe string duplication function
 * 
 * Private function that duplicates a string with proper memory allocation
 * 
 * @param s String to duplicate
 * @return char* Duplicated string, or NULL if allocation fails
 */
static char *my_strdup(const char *s) {
    if (s == NULL) return NULL;
    
    size_t len = strlen(s) + 1;
    char *copy = malloc(len);
    if (copy != NULL) {
        memcpy(copy, s, len);
    }
    return copy;
}