//
// Created by Qui Tran on 10/5/23.
//
#include <assert.h>
#include <ctype.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"

char* read_line() {
    size_t alloc_length = 1024;
    size_t data_length = 0;

    char* data = malloc(alloc_length);

    if (stdin == NULL){
        return NULL;
    }

    while (true) {
        char* cursor = data + data_length;
        char* line = fgets(cursor, alloc_length - data_length, stdin);

        if (!line) {
            break;
        }

        data_length += strlen(cursor);

        if (data_length < alloc_length - 1 || data[data_length - 1] == '\n') {
            break;
        }

        alloc_length <<= 1;

        data = realloc(data, alloc_length);

        if (!data) {
            data = "\0";

            break;
        }
    }

    if (data[data_length - 1] == '\n') {
        data[data_length - 1] = '\0';

        data = realloc(data, data_length);

        if (!data) {
            data = "\0";
        }
    } else {
        data = realloc(data, data_length + 1);

        if (!data) {
            data = "\0";
        } else {
            data[data_length] = '\0';
        }
    }

    return data;
}

char* left_trim(char* str){
    if (!str){
        return NULL;
    }

    if (!*str){
        return str;
    }

    while(*str != '\0' && isspace(*str)){
        str++;
    }

    return str;
}

/*
 *
 * */
char* right_trim(char* str){
    if(!str){
        return NULL;
    }

    if (!*str){
        return str;
    }

    //Get pointer to end character
    int len = strlen(str);

    //Trace back the space and calculate the len of return value
    while(isspace(str[len - 1])){
        len--;
    }
    char* result = strndup(str,len);
    return result;
}

/*
 *
 * */
char** split_string(char* str) {
    char** splits = NULL;

    if(str == NULL){
        return NULL;
    }

    // Duplicate the input string since strtok modifies it
    char* input_copy = strdup(str);
    if (input_copy == NULL) {
        return NULL; // Memory allocation failed
    }

    // Count the number of tokens (substrings)
    int spaces = 1;
    char* token = strtok(input_copy, " ");
    while (token != NULL) {
        spaces++;
        token = strtok(NULL, " ");
    }

    //Allocate memory
    splits = (char**) malloc(spaces * sizeof(char*));

    //Reset input_copy and tokenize again
    strcpy(input_copy, str);
    int token_index = 0;
    token = strtok(input_copy, " ");
    while(token != NULL){
        splits[token_index] = strdup(token);
        token_index++;
        token = strtok(NULL, " ");
    }
    return splits;
}

bool parse_int(char* str, int* result){
    char* endptr;
    *result = (int) strtol(str, &endptr, 10);
    if (*endptr != '\0'){
        return false;
    }
    return true;
}

int* reverse_array(int a_count, int* org_array, int* result_count){
    if (org_array == NULL){
        *result_count = 0;
        return NULL;
    }
    int* reversed_array = (int*) malloc(a_count * sizeof (int));
    if(reversed_array == NULL){
        *result_count = 0;
        return NULL;
    }

    for (int i = 0; i < a_count; i++){
        reversed_array[i] = org_array[a_count - 1 - i];
    }

    *result_count = a_count;
    return reversed_array;
}
