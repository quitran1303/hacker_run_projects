//
// Created by Qui Tran on 10/5/23.
//
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "unity/src/unity.h"
#include "../src/util.h"

void setUp(void){
    //set up necessary things
}

void tearDown(void){
    //Clean up things
}

void test_readline_with_valid_input(void){
    //Create a file for fake the stdin
    FILE* fake_stdin = fopen("fake_stdin.txt", "w+");
    if (fake_stdin == NULL){
        TEST_FAIL_MESSAGE("Can not read the fake_stdin.txt");
        return;
    }

    //Redirect stdin to fake_stdin
    stdin = fake_stdin;

    //Write line to file
    fprintf(fake_stdin, "This line is for testing");

    //Rewind the fake_stdin to beginning
    rewind(fake_stdin);

    //Call the read_line function
    char* result = read_line();

    //Check the result
    TEST_ASSERT_NOT_NULL(result);
    TEST_ASSERT_EQUAL_STRING("This line is for testing", result);

    //Free memory
    free(result);

    //Close the file ptr
    fclose(fake_stdin);
    remove("fake_stdin.txt");
}

void test_readline_with_null_input(void){
    //Assign NULL to stdin
    stdin = NULL;
    char* result = read_line();

    //Check if the result is null
    TEST_ASSERT_NULL(result);
}

void test_readline_with_empty_input(void) {
    // Create a FILE pointer to simulate stdin
    FILE* fake_stdin = fopen("fake_stdin.txt", "w+");
    if (fake_stdin == NULL) {
        TEST_FAIL_MESSAGE("Failed to open fake_stdin.txt");
        return;
    }

    // Redirect stdin to the fake_stdin file
    stdin = fake_stdin;

    // No input in fake_stdin

    // Call the read_line function
    char* result = read_line();

    // Check that the result is "" (due to empty input)
    TEST_ASSERT_EQUAL_STRING("",result);

    // Close fake_stdin
    fclose(fake_stdin);

    //Remove temp file after running
    remove("fake_stdin.txt");
}

//char* left_trim(char* str);
void test_ltrim_with_valid_input(void){
    char* string_with_left_spaces = "   abc";
    char* result = left_trim(string_with_left_spaces);

    TEST_ASSERT_NOT_NULL(result);
    TEST_ASSERT_EQUAL_STRING("abc", result);
}

void test_ltrim_with_null_input(void){
    char* string_null = NULL;
    char* result = left_trim(string_null);

    TEST_ASSERT_NULL(result);
}

void test_ltrim_with_all_spaces(void){
    char* string_all_spaces = "     ";
    char* result = left_trim(string_all_spaces);

    TEST_ASSERT_NOT_NULL(result);
    TEST_ASSERT_EMPTY(result);
}

void test_ltrim_with_no_spaces(void){
    char* string_no_spaces = "Hello World";
    char* result = left_trim(string_no_spaces);

    TEST_ASSERT_NOT_NULL(result);
    TEST_ASSERT_EQUAL_STRING("Hello World", result);

}

void test_ltrim_with_empty_string(void){
    char* string_empty = "";
    char* result = left_trim(string_empty);

    TEST_ASSERT_NOT_NULL(result);
    TEST_ASSERT_EQUAL_STRING("", result);
}

//RTRIM() testcases - char* right_trim(char* str);
void test_rtrim_with_empty_string(void){
    char* string_empty = "";
    char* result = right_trim(string_empty);

    //Not null and empry
    TEST_ASSERT_NOT_NULL(result);
    TEST_ASSERT_EQUAL_STRING("", result);
}

void test_rtrim_with_right_spaces(void){
    char* string_with_spaces = "Hello World   ";
    char* result = right_trim(string_with_spaces);

    TEST_ASSERT_NOT_NULL(result);
    TEST_ASSERT_EQUAL_STRING("Hello World", result);
}

void test_rtrim_with_all_spaces(void){
    char* string_with_all_spaces = "       ";
    char* result = right_trim(string_with_all_spaces);

    TEST_ASSERT_NOT_NULL(result);
    TEST_ASSERT_EQUAL_STRING("", result);
}

void test_rtrim_with_null(void){
    char* string_null = NULL;
    char* result = right_trim(string_null);

    TEST_ASSERT_NULL(result);
}

void test_rtrim_with_no_spaces(void){
    char* string_no_spaces = "Hello John";
    char* result = right_trim(string_no_spaces);

    TEST_ASSERT_NOT_NULL(result);
    TEST_ASSERT_EQUAL_STRING("Hello John", result);
}

// Test cases for char** split_string(char*);
//"this is for test", "", NULL, "   this is for test", "this is for test  ", "     "
void test_split_string_valid_input(void){
    char input[] = "Split This String";
    char** result = split_string(input);

    char* expected_result[] = {"Split", "This", "String"};
    // Check that the result is an array of tokens
    TEST_ASSERT_NOT_NULL(result);
    TEST_ASSERT_EQUAL_STRING_ARRAY(expected_result, result, 3);

    // Free the allocated memory
    for (int i = 0; result[i] != NULL; i++) {
        free(result[i]);
    }
    free(result);
}

void test_split_string_with_empty_string(void){
    char input[] = "";
    char** result = split_string(input);

    //Check the result
    TEST_ASSERT_NOT_NULL(result);
    TEST_ASSERT_EMPTY(result);
}

void test_split_string_with_null_string(void){
    char* input = NULL;
    char** result = split_string(input);

    //Check the result
    TEST_ASSERT_NULL(result);
}

void test_split_string_with_spaces_before(void){
    char input[] = "   This is spaces string";
    char** result = split_string(input);

    //Expected result array
    char* expected_result[] = {"This", "is", "spaces", "string"};
    //Check the result
    TEST_ASSERT_NOT_NULL(result);
    TEST_ASSERT_EQUAL_STRING_ARRAY(expected_result, result, 4);
}

void test_split_string_with_spaces_after(void){
    char input[] = "This is spaces string     ";
    char** result = split_string(input);

    //Expected result array
    char* expected_result[] = {"This", "is", "spaces", "string"};
    //Check the result
    TEST_ASSERT_NOT_NULL(result);
    TEST_ASSERT_EQUAL_STRING_ARRAY(expected_result, result, 4);
}

void test_split_string_with_all_spaces(void){
    char input[] = "        ";
    char** result = split_string(input);

    //Check the result
    TEST_ASSERT_NOT_NULL(result);
    TEST_ASSERT_EMPTY(result);
}

// Testcases for bool parse_int(char* str, int* result)
void test_parse_int_with_valid_input(void){
    char* input = "1234";
    int output_int;
    int parsing_result = parse_int(input, &output_int);

    TEST_ASSERT_NOT_NULL(output_int);
    TEST_ASSERT_EQUAL(true, parsing_result);
    TEST_ASSERT_EQUAL_INT(1234, output_int);
}

void test_parse_int_with_invalid_input(void){
    char* input = "abcd";
    int output_int;
    bool parsing_result = parse_int(input, &output_int);

    TEST_ASSERT_NULL(output_int);
    TEST_ASSERT_EQUAL(false, parsing_result);
}

// Testcases for reverse array function
void test_reverse_array_with_valid_input(void){
    int input_arr[] = {1,2,3,4};
    int result_count;

    int expected_arr[] = {4,3,2,1};

    int* result = reverse_array(4, input_arr, &result_count);
    TEST_ASSERT_EQUAL_INT(4,result_count);
    TEST_ASSERT_EQUAL_INT_ARRAY(expected_arr, result, 4);
}

void test_reverse_array_with_null_input(void){
    int result_count;
    int* result = reverse_array(0,NULL, &result_count);

    TEST_ASSERT_NULL(result);
    TEST_ASSERT_EQUAL_INT(0, result_count);

}

void test_reverse_array_with_empty_input(void){
    int input_array[] = {};
    int result_count;

    int* result = reverse_array(0, input_array, &result_count);

    TEST_ASSERT_EQUAL_INT(0, result_count);
    TEST_ASSERT_EMPTY(result);
}

int main(void) {
    UNITY_BEGIN();

    // Run the test case for function read_line
    RUN_TEST(test_readline_with_valid_input);
    RUN_TEST(test_readline_with_null_input);
    RUN_TEST(test_readline_with_empty_input);

    // Run the testcases for left_trim (left trim spaces)
    RUN_TEST(test_ltrim_with_valid_input);
    RUN_TEST(test_ltrim_with_null_input);
    RUN_TEST(test_ltrim_with_all_spaces);
    RUN_TEST(test_ltrim_with_no_spaces);
    RUN_TEST(test_ltrim_with_empty_string);

    // Run the testcases for right_trim (right trim spaces)
    RUN_TEST(test_rtrim_with_empty_string);
    RUN_TEST(test_rtrim_with_right_spaces);
    RUN_TEST(test_rtrim_with_all_spaces);
    RUN_TEST(test_rtrim_with_null);
    RUN_TEST(test_rtrim_with_no_spaces);

    // Run the testcases for split_string
    RUN_TEST(test_split_string_valid_input);
    RUN_TEST(test_split_string_with_empty_string);
    RUN_TEST(test_split_string_with_null_string);
    RUN_TEST(test_split_string_with_spaces_before);
    RUN_TEST(test_split_string_with_spaces_after);
    RUN_TEST(test_split_string_with_all_spaces);

    // Run the testcases for parse_in
    RUN_TEST(test_parse_int_with_valid_input);
    RUN_TEST(test_parse_int_with_invalid_input);

    // Run the testcases for reverse array
    RUN_TEST(test_reverse_array_with_valid_input);
    RUN_TEST(test_reverse_array_with_null_input);
    RUN_TEST(test_reverse_array_with_empty_input);

    return UNITY_END();
}