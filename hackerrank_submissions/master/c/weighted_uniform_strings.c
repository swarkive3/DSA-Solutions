/*
 * Contest: Master
 * Challenge: Weighted Uniform Strings
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
 * Complete the 'weightedUniformStrings' function below.
 *
 * The function is expected to return a STRING_ARRAY.
 * The function accepts following parameters:
 * 1. STRING s
 * 2. INTEGER_ARRAY queries
 */

char** weightedUniformStrings(char* s, int queries_count, int* queries, int* result_count) {
    // 1. Set result size
    *result_count = queries_count;
    
    // 2. Allocate memory for the array of return strings
    char** results = malloc(queries_count * sizeof(char*));
    
    // 3. Create a lookup table for possible weights.
    // Constraints: Queries can go up to 10^7.
    // We allocate roughly 10MB for a boolean-style lookup table.
    int MAX_WEIGHT = 10000000; 
    unsigned char* has_weight = calloc(MAX_WEIGHT + 1, sizeof(unsigned char));
    
    // 4. Iterate through the string to mark all uniform weights
    int len = strlen(s);
    int current_consecutive_len = 0;
    char prev_char = '\0';
    
    for (int i = 0; i < len; i++) {
        char current_char = s[i];
        
        // If current char matches previous, extend the sequence
        if (current_char == prev_char) {
            current_consecutive_len++;
        } else {
            // New character sequence starts
            current_consecutive_len = 1;
            prev_char = current_char;
        }
        
        // Calculate weight: (char index 1-26) * count
        // 'a' is 97, so 'a' - 'a' + 1 = 1
        int char_weight = current_char - 'a' + 1;
        int total_weight = char_weight * current_consecutive_len;
        
        // Mark this weight as existing in our lookup table
        if (total_weight <= MAX_WEIGHT) {
            has_weight[total_weight] = 1;
        }
    }
    
    // 5. Answer the queries
    for (int i = 0; i < queries_count; i++) {
        int q = queries[i];
        
        // Allocate space for "Yes" or "No" (4 chars including null terminator)
        results[i] = malloc(4 * sizeof(char));
        
        // Check lookup table (bounds check first to be safe)
        if (q <= MAX_WEIGHT && has_weight[q]) {
            strcpy(results[i], "Yes");
        } else {
            strcpy(results[i], "No");
        }
    }
    
    // Clean up our temporary lookup table
    free(has_weight);
    
    return results;
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    char* s = readline();

    int queries_count = parse_int(ltrim(rtrim(readline())));

    int* queries = malloc(queries_count * sizeof(int));

    for (int i = 0; i < queries_count; i++) {
        int queries_item = parse_int(ltrim(rtrim(readline())));

        *(queries + i) = queries_item;
    }

    int result_count;
    char** result = weightedUniformStrings(s, queries_count, queries, &result_count);

    for (int i = 0; i < result_count; i++) {
        fprintf(fptr, "%s", *(result + i));

        if (i != result_count - 1) {
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
