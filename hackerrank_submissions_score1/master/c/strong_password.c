/*
 * Contest: Master
 * Challenge: Strong Password
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

int minimumNumber(int n, char* password) {
    // 1. Initialize flags to track what we have found
    int has_digit = 0;
    int has_lower = 0;
    int has_upper = 0;
    int has_special = 0;
    
    // Define the special characters as given in the problem
    char *special_chars = "!@#$%^&*()-+";

    // 2. Iterate through the password to set flags
    for(int i = 0; i < n; i++) {
        char c = password[i];
        
        if (isdigit(c)) {
            has_digit = 1;
        } else if (islower(c)) {
            has_lower = 1;
        } else if (isupper(c)) {
            has_upper = 1;
        } else if (strchr(special_chars, c) != NULL) {
            // strchr returns a pointer if the character is found, NULL otherwise
            has_special = 1;
        }
    }

    // 3. Count how many required types are missing
    int missing_types = 0;
    if (!has_digit) missing_types++;
    if (!has_lower) missing_types++;
    if (!has_upper) missing_types++;
    if (!has_special) missing_types++;

    // 4. Calculate how many characters we need just to satisfy length 6
    int length_deficit = 6 - n;
    if (length_deficit < 0) length_deficit = 0;

    // 5. The result is the maximum of the two requirements
    if (missing_types > length_deficit) {
        return missing_types;
    } else {
        return length_deficit;
    }
}
int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    int n = parse_int(ltrim(rtrim(readline())));

    char* password = readline();

    int answer = minimumNumber(n, password);

    fprintf(fptr, "%d\n", answer);

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
