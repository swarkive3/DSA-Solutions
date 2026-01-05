/*
 * Contest: Master
 * Challenge: Separate the Numbers
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

void separateNumbers(char* s) {
    int len = strlen(s);
    
    // A beautiful string must have at least 2 numbers, so a string of length 1 is always NO.
    if (len < 2) {
        printf("NO\n");
        return;
    }

    // Try all possible lengths for the first number (up to half the string)
    for (int i = 1; i <= len / 2; i++) {
        
        // Construct the first number substring
        char firstStr[33];
        strncpy(firstStr, s, i);
        firstStr[i] = '\0'; // Null-terminate manually
        
        // Constraint Check: The first number cannot have a leading zero (unless the number is just "0")
        // However, looking at sample 010203 -> NO, implies we cannot treat "01" as "1".
        // If the length is > 1 and it starts with '0', this split is invalid.
        if (i > 1 && firstStr[0] == '0') {
            break; 
        }

        // Convert to long long for math operations
        unsigned long long firstNum = strtoull(firstStr, NULL, 10);
        unsigned long long currentNum = firstNum;
        
        // Build the sequence string to compare
        char buildStr[200]; // Buffer to hold the constructed sequence
        buildStr[0] = '\0';
        strcpy(buildStr, firstStr);
        
        // While our built string is shorter than the input string, keep adding next numbers
        while (strlen(buildStr) < len) {
            currentNum++;
            char nextNumStr[33];
            sprintf(nextNumStr, "%llu", currentNum);
            strcat(buildStr, nextNumStr);
        }
        
        // Compare the built string with the original input
        if (strcmp(buildStr, s) == 0) {
            printf("YES %s\n", firstStr);
            return;
        }
    }
    
    printf("NO\n");
}

int main()
{
    int q = parse_int(ltrim(rtrim(readline())));

    for (int q_itr = 0; q_itr < q; q_itr++) {
        char* s = readline();

        separateNumbers(s);
    }

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
