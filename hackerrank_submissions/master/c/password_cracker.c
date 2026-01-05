/*
 * Contest: Master
 * Challenge: Password Cracker
 * Language: c
 * Score: 0.0
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

#define MAX_LEN 2005

// Global arrays to store state during recursion
// memo[i] stores: -1 (unknown), 0 (failed), 1 (success)
int memo[MAX_LEN];
// path[i] stores the index of the password used to bridge the gap starting at 'i'
int path[MAX_LEN];

// Helper function: Depth First Search with Memoization
// Returns 1 if solvable, 0 if not
int solve(int idx, int n, char** passwords, char* loginAttempt, int len_login) {
    // Base Case: We reached the exact end of the string
    if (idx == len_login) {
        return 1;
    }

    // Check if we have already visited this state
    if (memo[idx] != -1) {
        return memo[idx];
    }

    // Try every password to see if it matches the current position
    for (int i = 0; i < n; i++) {
        int pass_len = strlen(passwords[i]);

        // 1. Check if the password fits within the remaining length
        // 2. Check if the characters match exactly
        if (idx + pass_len <= len_login && strncmp(loginAttempt + idx, passwords[i], pass_len) == 0) {
            
            // If it matches, recursively try to solve the rest
            if (solve(idx + pass_len, n, passwords, loginAttempt, len_login)) {
                memo[idx] = 1;      // Mark this index as solvable
                path[idx] = i;      // Record that we used password 'i' here
                return 1;
            }
        }
    }

    // If no password worked, mark this index as a dead end
    memo[idx] = 0;
    return 0;
}

char* passwordCracker(int passwords_count, char** passwords, char* loginAttempt) {
    int len_login = strlen(loginAttempt);

    // Initialize memoization array to -1 (unknown state)
    for (int i = 0; i <= len_login; i++) {
        memo[i] = -1;
    }

    // Start the recursive solver from index 0
    if (solve(0, passwords_count, passwords, loginAttempt, len_login)) {
        // --- Success: Reconstruct the string ---
        
        // Allocate memory for the result. 
        // Max length is roughly len_login + spaces. 4096 is plenty safe.
        char* result = malloc(4096 * sizeof(char));
        result[0] = '\0'; // Start with an empty string

        int curr = 0;
        while (curr < len_login) {
            int p_idx = path[curr]; // Retrieve the password index used at this step
            
            strcat(result, passwords[p_idx]);
            curr += strlen(passwords[p_idx]); // Move the cursor forward
            
            // Append a space only if we haven't reached the end
            if (curr < len_login) {
                strcat(result, " ");
            }
        }
        return result;
    } else {
        // --- Failure ---
        char* wrong = malloc(20 * sizeof(char));
        strcpy(wrong, "WRONG PASSWORD");
        return wrong;
    }
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    int t = parse_int(ltrim(rtrim(readline())));

    for (int t_itr = 0; t_itr < t; t_itr++) {
        int n = parse_int(ltrim(rtrim(readline())));

        char** passwords_temp = split_string(rtrim(readline()));

        char** passwords = malloc(n * sizeof(char*));

        for (int i = 0; i < n; i++) {
            char* passwords_item = *(passwords_temp + i);

            *(passwords + i) = passwords_item;
        }

        char* loginAttempt = readline();

        char* result = passwordCracker(n, passwords, loginAttempt);

        fprintf(fptr, "%s\n", result);
    }

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

char** split_string(char* str) {
    char** splits = NULL;
    char* token = strtok(str, " ");

    int spaces = 0;

    while (token) {
        splits = realloc(splits, sizeof(char*) * ++spaces);

        if (!splits) {
            return splits;
        }

        splits[spaces - 1] = token;

        token = strtok(NULL, " ");
    }

    return splits;
}

int parse_int(char* str) {
    char* endptr;
    int value = strtol(str, &endptr, 10);

    if (endptr == str || *endptr != '\0') {
        exit(EXIT_FAILURE);
    }

    return value;
}
