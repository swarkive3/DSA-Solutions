/*
 * Contest: Master
 * Challenge: Bear and Steady Gene
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
 * Complete the 'steadyGene' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts STRING gene as parameter.
 */

int steadyGene(char* gene) {
    int n = strlen(gene);
    int target = n / 4;
    
    // 1. Count frequencies of each nucleotide in the entire gene
    // We use size 128 to accommodate standard ASCII characters ('A', 'C', 'G', 'T') directly.
    int count[128] = {0};
    for (int i = 0; i < n; i++) {
        count[gene[i]]++;
    }

    // 2. Check if the gene is already steady
    // If no character exceeds the target frequency, we don't need to change anything.
    if (count['A'] <= target && count['C'] <= target && 
        count['G'] <= target && count['T'] <= target) {
        return 0;
    }

    int min_len = n;
    int left = 0;
    int right = 0;

    // 3. Sliding Window (Two Pointers)
    // We expand the window (right) and effectively "remove" characters inside it from the total counts.
    // If the remaining characters (outside the window) all satisfy the count <= target condition,
    // it means we can replace the window content to make the gene steady.
    for (right = 0; right < n; right++) {
        
        // Remove the character at 'right' from the count (it's now inside the window)
        count[gene[right]]--;

        // While the counts outside the window are valid (all <= target),
        // try to shrink the window from the left to find the minimum length.
        while (count['A'] <= target && count['C'] <= target && 
               count['G'] <= target && count['T'] <= target) {
            
            // Update minimum length found so far
            int current_len = right - left + 1;
            if (current_len < min_len) {
                min_len = current_len;
            }

            // Shrink from left: Add the character back to the count (it goes outside the window)
            count[gene[left]]++;
            left++;
        }
    }

    return min_len;
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    int n = parse_int(ltrim(rtrim(readline())));

    char* gene = readline();

    int result = steadyGene(gene);

    fprintf(fptr, "%d\n", result);

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
