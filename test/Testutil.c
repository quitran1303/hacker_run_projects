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
}

int main(void) {
    UNITY_BEGIN();

    // Run the test case
    RUN_TEST(test_readline_with_valid_input);

    return UNITY_END();
}