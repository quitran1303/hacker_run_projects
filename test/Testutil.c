//
// Created by Qui Tran on 10/5/23.
//
#include <stdio.h>
#include <stdlib.h>
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

    //Call the readline function
    char* result = readline();

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
    char* result = readline();

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

    // Call the readline function
    char* result = readline();

    // Check that the result is "" (due to empty input)
    TEST_ASSERT_EQUAL_STRING("",result);

    // Close fake_stdin
    fclose(fake_stdin);

    //Remove temp file after running
    remove("fake_stdin.txt");
}

//char* ltrim(char* str);
void test_ltrim_with_valid_input(void){
    char* string_with_left_spaces = "   abc";
    char* result = ltrim(string_with_left_spaces);

    TEST_ASSERT_NOT_NULL(result);
    TEST_ASSERT_EQUAL_STRING("abc", result);
}

void test_ltrim_with_null_input(void){
    char* string_null = NULL;
    char* result = ltrim(string_null);

    TEST_ASSERT_NULL(result);
}

void test_ltrim_with_all_spaces(void){
    char* string_all_spaces = "     ";
    char* result = ltrim(string_all_spaces);

    TEST_ASSERT_NOT_NULL(result);
    TEST_ASSERT_EMPTY(result);
}

void test_ltrim_with_no_spaces(void){
    char* string_no_spaces = "Hello World";
    char* result = ltrim(string_no_spaces);

    TEST_ASSERT_NOT_NULL(result);
    TEST_ASSERT_EQUAL_STRING("Hello World", result);

}

void test_ltrim_with_empty_string(void){
    char* string_empty = "";
    char* result = ltrim(string_empty);

    TEST_ASSERT_NOT_NULL(result);
    TEST_ASSERT_EQUAL_STRING("", result);
}

//RTRIM() testcases - char* rtrim(char* str);
void test_rtrim_with_empty_string(void){
    char* string_empty = "";
    char* result = rtrim(string_empty);

    //Not null and empry
    TEST_ASSERT_NOT_NULL(result);
    TEST_ASSERT_EQUAL_STRING("", result);
}

void test_rtrim_with_right_spaces(void){
    char* string_with_spaces = "Hello World   ";
    char* result = rtrim(string_with_spaces);

    TEST_ASSERT_NOT_NULL(result);
    TEST_ASSERT_EQUAL_STRING("Hello World", result);
}

void test_rtrim_with_all_spaces(void){
    char* string_with_all_spaces = "       ";
    char* result = rtrim(string_with_all_spaces);

    TEST_ASSERT_NOT_NULL(result);
    TEST_ASSERT_EQUAL_STRING("", result);
}

void test_rtrim_with_null(void){
    char* string_null = NULL;
    char* result = rtrim(string_null);

    TEST_ASSERT_NULL(result);
}

void test_rtrim_with_no_spaces(void){
    char* string_no_spaces = "Hello John";
    char* result = rtrim(string_no_spaces);

    TEST_ASSERT_NOT_NULL(result);
    TEST_ASSERT_EQUAL_STRING("Hello John", result);
}

int main(void) {
    UNITY_BEGIN();

    // Run the test case for function readline
    RUN_TEST(test_readline_with_valid_input);
    RUN_TEST(test_readline_with_null_input);
    RUN_TEST(test_readline_with_empty_input);

    // Run the testcases for ltrim (left trim spaces)
    RUN_TEST(test_ltrim_with_valid_input);
    RUN_TEST(test_ltrim_with_null_input);
    RUN_TEST(test_ltrim_with_all_spaces);
    RUN_TEST(test_ltrim_with_no_spaces);
    RUN_TEST(test_ltrim_with_empty_string);

    //Run the testcases for rtrim (right trim spaces)
    RUN_TEST(test_rtrim_with_empty_string);
    RUN_TEST(test_rtrim_with_right_spaces);
    RUN_TEST(test_rtrim_with_all_spaces);
    RUN_TEST(test_rtrim_with_null);
    RUN_TEST(test_rtrim_with_no_spaces);

    return UNITY_END();
}