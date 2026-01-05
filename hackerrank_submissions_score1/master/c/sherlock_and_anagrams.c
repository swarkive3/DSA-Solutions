/*
 * Contest: Master
 * Challenge: Sherlock and Anagrams
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
 * Complete the 'sherlockAndAnagrams' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts STRING s as parameter.
 */

int sherlockAndAnagrams(char* s) {
    int length = strlen(s);
    int anagramPairs = 0;

    // 1. Iterate over all possible substring lengths (from 1 to length - 1)
    // We don't need to check length because a string is an anagram of itself, 
    // but the problem asks for pairs of substrings.
    for (int subLen = 1; subLen < length; subLen++) {
        
        // 2. Iterate through all starting positions for the first substring
        for (int i = 0; i <= length - subLen; i++) {
            
            // 3. Iterate through all starting positions for the second substring
            // We start 'j' from i + 1 to avoid counting the same pair twice or comparing a substring to itself.
            for (int j = i + 1; j <= length - subLen; j++) {
                
                // 4. Check if substring s[i...i+subLen] is an anagram of s[j...j+subLen]
                
                // Frequency array for 26 lowercase letters
                int freq[26] = {0};

                // Increment counts for the first substring
                for (int k = 0; k < subLen; k++) {
                    freq[s[i + k] - 'a']++;
                }

                // Decrement counts for the second substring
                for (int k = 0; k < subLen; k++) {
                    freq[s[j + k] - 'a']--;
                }

                // If substrings are anagrams, the frequency array should be all zeros.
                int isAnagram = 1;
                for (int k = 0; k < 26; k++) {
                    if (freq[k] != 0) {
                        isAnagram = 0;
                        break;
                    }
                }

                if (isAnagram) {
                    anagramPairs++;
                }
            }
        }
    }

    return anagramPairs;
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    int q = parse_int(ltrim(rtrim(readline())));

    for (int q_itr = 0; q_itr < q; q_itr++) {
        char* s = readline();

        int result = sherlockAndAnagrams(s);

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
