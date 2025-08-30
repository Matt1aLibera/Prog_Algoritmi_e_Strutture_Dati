#include "test_ex2.h"

// ==================== TEST UTILITY FUNCTIONS ====================

void assert_edit_distance(const char *s1, const char *s2, int expected, const char *test_name) {
    int result1 = edit_distance(s1, s2);
    int result2 = edit_distance_dyn(s1, s2);
    
    if (result1 != expected || result2 != expected || result1 != result2) {
        printf("FAIL: %s - Expected %d, got recursive=%d, dynamic=%d for '%s' -> '%s'\n", 
               test_name, expected, result1, result2, s2, s1);
        assert(0);
    }
    printf("PASS: %s\n", test_name);
}

void assert_null_handling(void) {
    int result1 = edit_distance(NULL, "test");
    int result2 = edit_distance("test", NULL);
    int result3 = edit_distance_dyn(NULL, "test");
    int result4 = edit_distance_dyn("test", NULL);
    
    if (result1 != -1 || result2 != -1 || result3 != -1 || result4 != -1) {
        printf("FAIL: assert_null_handling - Expected -1 for NULL inputs\n");
        assert(0);
    }
    printf("PASS: assert_null_handling\n");
}

// ==================== TEST BASE CASES ====================

void test_empty_strings(void) {
    assert_edit_distance("", "", 0, "test_empty_strings");
}

void test_first_string_empty(void) {
    assert_edit_distance("", "hello", 5, "test_first_string_empty");
}

void test_second_string_empty(void) {
    assert_edit_distance("world", "", 5, "test_second_string_empty");
}

// ==================== TEST EQUAL STRINGS ====================

void test_equal_strings(void) {
    assert_edit_distance("hello", "hello", 0, "test_equal_strings");
    assert_edit_distance("a", "a", 0, "test_equal_single_char");
    assert_edit_distance("longerstring", "longerstring", 0, "test_equal_long_strings");
}

// ==================== TEST SINGLE OPERATION CASES ====================

void test_single_deletion(void) {
    assert_edit_distance("casa", "cassa", 1, "test_single_deletion");
    assert_edit_distance("est", "test", 1, "test_single_deletion_beginning");
    assert_edit_distance("hell", "hello", 1, "test_single_deletion_end");
}

void test_single_insertion(void) {
    assert_edit_distance("cassa", "casa", 1, "test_single_insertion");
    assert_edit_distance("test", "est", 1, "test_single_insertion_beginning");
    assert_edit_distance("hello", "hell", 1, "test_single_insertion_end");
}

// ==================== TEST MULTIPLE OPERATIONS ====================

void test_multiple_operations(void) {
    assert_edit_distance("casa", "cara", 2, "test_multiple_operations_1");
    assert_edit_distance("vinaio", "vino", 2, "test_multiple_operations_2");
    assert_edit_distance("tassa", "passato", 4, "test_multiple_operations_3");
    assert_edit_distance("kitten", "sitting", 5, "test_multiple_operations_4");
}

// ==================== TEST COMPLEX CASES ====================

void test_completely_different_strings(void) {
    assert_edit_distance("abc", "def", 6, "test_completely_different_strings");
    assert_edit_distance("hello", "world", 8, "test_completely_different_words");
}

void test_substring_relationships(void) {
    assert_edit_distance("programming", "program", 4, "test_substring_relationships_1");
    assert_edit_distance("algorithm", "algebra", 8, "test_substring_relationships_2");
}

void test_prefix_suffix_cases(void) {
    assert_edit_distance("unhappy", "happy", 2, "test_prefix_case");
    assert_edit_distance("happiness", "happy", 6, "test_suffix_case");
}

// ==================== TEST EDGE CASES ====================

void test_single_char_strings(void) {
    assert_edit_distance("a", "b", 2, "test_different_single_chars");
    assert_edit_distance("a", "a", 0, "test_same_single_chars");
    assert_edit_distance("a", "", 1, "test_single_char_vs_empty");
    assert_edit_distance("", "a", 1, "test_empty_vs_single_char");
}

// ==================== TEST CONSISTENCY BETWEEN FUNCTIONS ====================

void test_consistency_across_functions(void) {
    const char *test_cases[][2] = {
        {"", ""},
        {"a", ""},
        {"", "b"},
        {"hello", "hello"},
        {"casa", "cassa"},
        {"casa", "cara"},
        {"vinaio", "vino"},
        {"tassa", "passato"},
        {"kitten", "sitting"},
        {"programming", "program"},
        {"unhappy", "happy"}
    };
    
    for (size_t i = 0; i < sizeof(test_cases) / sizeof(test_cases[0]); i++) {
        const char *s1 = test_cases[i][0];
        const char *s2 = test_cases[i][1];
        
        int result1 = edit_distance(s1, s2);
        int result2 = edit_distance_dyn(s1, s2);
        
        if (result1 != result2) {
            printf("FAIL: test_consistency_across_functions - Results differ for '%s' -> '%s': recursive=%d, dynamic=%d\n",
                   s2, s1, result1, result2);
            assert(0);
        }
    }
    printf("PASS: test_consistency_across_functions\n");
}

// ==================== TEST MIN FUNCTION ====================

void test_min_functions(void) {
    // Test min3
    if (min3(1, 2, 3) != 1 || min3(3, 2, 1) != 1 || min3(2, 1, 3) != 1 ||
        min3(5, 5, 5) != 5 || min3(INT_MAX, 5, 10) != 5) {
        printf("FAIL: test_min_functions - min3 not working correctly\n");
        assert(0);
    }
    
    printf("PASS: test_min_functions\n");
}

// ==================== MAIN TEST RUNNER ====================

int main(void) {
    printf("=== Running Edit Distance Tests ===\n\n");
    
    // Test utility functions
    test_min_functions();
    printf("\n");
    
    // Test null handling
    assert_null_handling();
    printf("\n");
    
    // Test base cases
    test_empty_strings();
    test_first_string_empty();
    test_second_string_empty();
    printf("\n");
    
    // Test equal strings
    test_equal_strings();
    printf("\n");
    
    // Test single operation cases
    test_single_deletion();
    test_single_insertion();
    printf("\n");
    
    // Test multiple operations
    test_multiple_operations();
    printf("\n");
    
    // Test complex cases
    test_completely_different_strings();
    test_substring_relationships();
    test_prefix_suffix_cases();
    printf("\n");
    
    // Test edge cases
    test_single_char_strings();
    printf("\n");
    
    // Test consistency
    test_consistency_across_functions();
    printf("\n");
    
    printf("=== All Edit Distance tests passed! ===\n");
    return 0;
}