/*
 * Contest: Master
 * Challenge: Down to Zero II
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
 * Complete the 'downToZero' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts INTEGER n as parameter.
 */

#define MAX_VAL 1000001

// Global array to store precomputed distances
// Using static/global avoids stack overflow and re-computation
int dist[MAX_VAL];
int computed = 0;

void precompute() {
    // 1. Initialize with the worst-case moves (just subtracting 1)
    // dist[0] = 0, dist[1] = 1, dist[2] = 2, ...
    for (int i = 0; i < MAX_VAL; i++) {
        dist[i] = i;
    }

    // 2. Iterate through all numbers to find shortcuts
    for (int i = 0; i < MAX_VAL; i++) {
        
        // --- Forward Propagate Subtraction Move ---
        // If we are at 'i', we can reach 'i+1' in reverse (conceptually N-1 move)
        if (i + 1 < MAX_VAL) {
            if (dist[i + 1] > dist[i] + 1) {
                dist[i + 1] = dist[i] + 1;
            }
        }

        // --- Forward Propagate Factor Move ---
        // If we are at 'i', we can reach any multiple 'prod = i * j'
        // This corresponds to the move N -> max(a, b) where a=i, b=j.
        // We only need to check j <= i because if j > i, we would cover it 
        // when the main loop reaches j.
        if (i >= 2) {
            for (int j = 2; j <= i && (long long)i * j < MAX_VAL; j++) {
                int prod = i * j;
                if (dist[prod] > dist[i] + 1) {
                    dist[prod] = dist[i] + 1;
                }
            }
        }
    }
}

int downToZero(int n) {
    // Run the precomputation only once
    if (!computed) {
        precompute();
        computed = 1;
    }
    
    return dist[n];
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    int q = parse_int(ltrim(rtrim(readline())));

    for (int q_itr = 0; q_itr < q; q_itr++) {
        int n = parse_int(ltrim(rtrim(readline())));

        int result = downToZero(n);

        fprintf(fptr, "%d\n", result);
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

int parse_int(char* str) {
    char* endptr;
    int value = strtol(str, &endptr, 10);

    if (endptr == str || *endptr != '\0') {
        exit(EXIT_FAILURE);
    }

    return value;
}
