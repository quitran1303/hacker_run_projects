//
// Created by Qui Tran on 10/5/23.
//

#ifndef HACKER_RUN_PROJECTS_UTIL_H
#define HACKER_RUN_PROJECTS_UTIL_H
char* read_line();
char* left_trim(char* str);
char* right_trim(char* str);
char** split_string(char* str);
bool parse_int(char* str, int* result);
int* reverse_array(int a_count, int* org_array, int* result_count);
int hourglass_sum(int arr_rows, int arr_columns, int** arr);
#endif //HACKER_RUN_PROJECTS_UTIL_H
