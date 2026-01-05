/*
 * Contest: Master
 * Challenge: Maximum Element
 * Language: c
 * Score: 1.0
 */

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

char* readline();
char* ltrim(char*);
char* rtrim(char*);

int parse_int(char*);

/*
 * Complete the 'getMax' function below.
 *
 * The function is expected to return an INTEGER_ARRAY.
 * The function accepts STRING_ARRAY operations as parameter.
 */

int* getMax(int operations_count, char** operations, int* result_count) {
    // 1. Allocate memory for the result array. 
    // Worst case: every operation is a type 3 query.
    int* result = malloc(sizeof(int) * operations_count);
    int res_idx = 0;

    // 2. Allocate memory for our "max stack".
    // This stack tracks the maximum value seen so far at every level.
    int* max_stack = malloc(sizeof(int) * operations_count);
    int top = -1; // Stack pointer, -1 indicates empty

    for (int i = 0; i < operations_count; i++) {
        char* op = operations[i];
        
        // The first character determines the type (1, 2, or 3)
        int type = op[0] - '0';

        if (type == 1) {
            // --- Push Operation ---
            // Parse the number x (skip "1 " which is 2 characters)
            int x = strtol(op + 2, NULL, 10);
            
            top++;
            if (top == 0) {
                // Stack was empty, x is the new max
                max_stack[top] = x;
            } else {
                // Compare x with the max value directly below it
                if (x > max_stack[top - 1]) {
                    max_stack[top] = x;
                } else {
                    max_stack[top] = max_stack[top - 1];
                }
            }
        } 
        else if (type == 2) {
            // --- Pop Operation ---
            if (top >= 0) {
                top--;
            }
        } 
        else if (type == 3) {
            // --- Print Max Operation ---
            if (top >= 0) {
                result[res_idx++] = max_stack[top];
            }
        }
    }

    // Free the helper stack memory
    free(max_stack);

    // Set the output size and return the result array
    *result_count = res_idx;
    return result;
}
int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    int n = parse_int(ltrim(rtrim(readline())));

    char** ops = malloc(n * sizeof(char*));

    for (int i = 0; i < n; i++) {
        char* ops_item = readline();

        *(ops + i) = ops_item;
    }

    int res_count;
    int* res = getMax(n, ops, &res_count);

    for (int i = 0; i < res_count; i++) {
        fprintf(fptr, "%d", *(res + i));

        if (i != res_count - 1) {
            fprintf(fptr, "\n");
        }
    }

    fprintf(fptr, "\n");

    fclose(fptr);

    return 0;
}

char* readline() {
    size_t alloc_length = 1024;
    size_t data_length = 0;

    char* data = malloc(alloc_length);

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
            data = '\0';

            break;
        }
    }

    if (data[data_length - 1] == '\n') {
        data[data_length - 1] = '\0';

        data = realloc(data, data_length);

        if (!data) {
            data = '\0';
        }
    } else {
        data = realloc(data, data_length + 1);

        if (!data) {
            data = '\0';
        } else {
            data[data_length] = '\0';
        }
    }

    return data;
}

char* ltrim(char* str) {
    if (!str) {
        return '\0';
    }

    if (!*str) {
        return str;
    }

    while (*str != '\0' && isspace(*str)) {
        str++;
    }

    return str;
}

char* rtrim(char* str) {
    if (!str) {
        return '\0';
    }

    if (!*str) {
        return str;
    }

    char* end = str + strlen(str) - 1;

    while (end >= str && isspace(*end)) {
        end--;
    }

    *(end + 1) = '\0';

    return str;
}

int parse_int(char* str) {
    char* endptr;
    int value = strtol(str, &endptr, 10);

    if (endptr == str || *endptr != '\0') {
        exit(EXIT_FAILURE);
    }

    return value;
}
