#include "main_ex1.h"
#include "sorting_algorithms.h"
//use "./bin/main_ex1 csv/records.csv csv/sorted.csv 1 1" to run the main

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

void sorting_controller(void *array, size_t element_count, size_t element_size, size_t algorithm, int (*comparator)(const void*, const void*)) {
    
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

void free_data_records(DataRecord *records, unsigned long record_count) {
    if (records == NULL) return;

    for (unsigned long i = 0; i < record_count; i++) {
        if (records[i].field1 != NULL) {
            free(records[i].field1);
            records[i].field1 = NULL; // Imposta a NULL dopo il free
        }
    }
    free(records); 
}


int compare_int_field(const void *a, const void *b) {
    
    const DataRecord *record_a = (const DataRecord*)a; 
    const DataRecord *record_b = (const DataRecord*)b; 

    // Evita overflow per numeri molto grandi
    if (record_a->field2 < record_b->field2) return -1;
    if (record_a->field2 > record_b->field2) return 1;
    return 0;
}


int compare_string_field(const void *a, const void *b) {
    
    const DataRecord *record_a = (const DataRecord*)a; 
    const DataRecord *record_b = (const DataRecord*)b;

    // Gestione sicura di stringhe NULL
    if (record_a->field1 == NULL && record_b->field1 == NULL) return 0;
    if (record_a->field1 == NULL) return -1;
    if (record_b->field1 == NULL) return 1;

    return strcmp(record_a->field1, record_b->field1);
}


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

DataRecord* read_data_records(FILE *input_file, unsigned long *record_count) {
    char line_buffer[BUFFER_SIZE];
    unsigned long current_capacity = *record_count;
    unsigned long records_read = 0;
    DataRecord *record_array = malloc(current_capacity * sizeof(DataRecord));

    if (record_array == NULL) {
        fprintf(stderr, "Memory allocation failed for record array\n");
        exit(EXIT_FAILURE);
    }

    for (unsigned long i = 0; i < current_capacity; i++) {
        record_array[i].field1 = NULL;
        record_array[i].id = 0;
        record_array[i].field2 = 0;
        record_array[i].field3 = 0.0;
    }

    while (fgets(line_buffer, BUFFER_SIZE, input_file) != NULL) {
        // Remove newline character if present
        line_buffer[strcspn(line_buffer, "\n")] = '\0';
        
        if (records_read == current_capacity) {
            current_capacity = (current_capacity * 3) / 2 + 1; // 1.5x growth
            DataRecord *temp = realloc(record_array, current_capacity * sizeof(DataRecord));
            if (temp == NULL) {
                fprintf(stderr, "Memory reallocation failed during reading\n");
                free_data_records(record_array, records_read);
                exit(EXIT_FAILURE);
            }
            record_array = temp;

            // Inizializza i nuovi elementi
             for (unsigned long i = records_read; i < current_capacity; i++) {
                record_array[i].field1 = NULL;
                record_array[i].id = 0;
                record_array[i].field2 = 0;
                record_array[i].field3 = 0.0;
            }
        }

        // Parse CSV fields using sscanf for better safety
        int id_value;
        int int_field;
        double double_field;
        char string_field[512]; // Temporary buffer for string field

        int parse_result = sscanf(line_buffer, "%d, %511[^,], %d, %lf", 
                                 &id_value, string_field, &int_field, &double_field);

        if (parse_result != 4) {
            fprintf(stderr, "Error: Failed to parse line %lu - invalid format\n", records_read + 1);
            // INIZIALIZZA COMUNQUE LA STRUTTURA
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

    // Resize to exact number of records read
    /*if (records_read > 0) {
        DataRecord *temp = realloc(record_array, records_read * sizeof(DataRecord));
        if (temp == NULL) {
            fprintf(stderr, "Warning: Final memory resize failed, using original allocation\n");
        } else {
            record_array = temp;
        }
    }*/

    *record_count = records_read;
    return record_array;
}

static char *my_strdup(const char *s) {
    if (s == NULL) return NULL;
    
    size_t len = strlen(s) + 1;
    char *copy = malloc(len);
    if (copy != NULL) {
        memcpy(copy, s, len);
    }
    return copy;
};