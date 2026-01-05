/*
 * Contest: Master
 * Challenge: Sherlock and the Valid String
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

/*
 * Complete the 'isValid' function below.
 *
 * The function is expected to return a STRING.
 * The function accepts STRING s as parameter.
 */

char* isValid(char* s) {
    // 1. Frequency Analysis
    // Count how many times each character appears in the string.
    int char_counts[26] = {0};
    int len = strlen(s);
    for (int i = 0; i < len; i++) {
        char_counts[s[i] - 'a']++;
    }

    // 2. Frequency of Frequencies
    // We need to know how many characters have a frequency of 1, how many have 2, etc.
    // Example: "aabbcc" -> char_counts=[2,2,2,...] -> freq_of_freqs[2] = 3
    // The maximum possible frequency for a char is the length of the string 'len'.
    // We allocate len+1 to be safe and use calloc to init to 0.
    int* freq_of_freqs = (int*)calloc(len + 1, sizeof(int));
    
    for (int i = 0; i < 26; i++) {
        if (char_counts[i] > 0) {
            freq_of_freqs[char_counts[i]]++;
        }
    }

    // 3. Analyze the Distribution
    // Find which frequencies actually exist (are non-zero).
    int first_freq = 0, second_freq = 0;
    int first_count = 0, second_count = 0;
    int distinct_freq_count = 0;

    for (int i = 1; i <= len; i++) {
        if (freq_of_freqs[i] > 0) {
            distinct_freq_count++;
            if (first_freq == 0) {
                first_freq = i;
                first_count = freq_of_freqs[i];
            } else {
                second_freq = i;
                second_count = freq_of_freqs[i];
            }
        }
    }
    
    // Clean up allocated memory
    free(freq_of_freqs);

    // 4. Determine Validity based on rules
    
    // Case A: All characters appear the same number of times.
    // e.g., "aabbcc" (all appear 2 times). distinct_freq_count == 1.
    if (distinct_freq_count == 1) {
        return "YES";
    }

    // Case B: More than 2 different frequencies.
    // e.g., "aabbcde" -> freq 2, 2, 1, 1, 1. (Frequencies present: 1 and 2).
    // If we have 3 or more different frequencies (e.g., frequencies 2, 3, and 5 exist),
    // removing just one character can never fix it.
    if (distinct_freq_count > 2) {
        return "NO";
    }

    // Case C: Exactly two different frequencies.
    // We must be able to remove exactly ONE character to satisfy the condition.
    
    // Subcase C1: The "aberrant" frequency is 1, and it only appears once.
    // Example: "aabbc" -> Frequencies: 2 (appears twice), 1 (appears once).
    // If we remove the character with frequency 1, it disappears, leaving only frequency 2.
    if (first_freq == 1 && first_count == 1) {
        return "YES";
    }
    if (second_freq == 1 && second_count == 1) {
        return "YES";
    }

    // Subcase C2: The higher frequency is exactly (lower frequency + 1), 
    // and the higher frequency appears exactly once.
    // Example: "aabbccc" -> Frequencies: 2 (appears twice), 3 (appears once).
    // If we remove one 'c', its frequency drops from 3 to 2, matching the others.
    int max_freq = (first_freq > second_freq) ? first_freq : second_freq;
    int min_freq = (first_freq < second_freq) ? first_freq : second_freq;
    int count_of_max = (first_freq > second_freq) ? first_count : second_count;

    if ((max_freq - min_freq == 1) && count_of_max == 1) {
        return "YES";
    }

    // If none of the valid cases match
    return "NO";
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    char* s = readline();

    char* result = isValid(s);

    fprintf(fptr, "%s\n", result);

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
