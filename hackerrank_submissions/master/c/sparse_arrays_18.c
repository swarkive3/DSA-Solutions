/*
 * Contest: Master
 * Challenge: Sparse Arrays
 * Language: c
 * Score: 1.0
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * The Logic Function
 */
int* matchingStrings(int stringList_count, char** stringList, int queries_count, char** queries, int* result_count) {
    // 1. Set the size of the result array (it matches the number of queries)
    *result_count = queries_count;

    // 2. Allocate memory for the results
    int* results = (int*)malloc(queries_count * sizeof(int));

    // 3. Loop through each query string
    for (int i = 0; i < queries_count; i++) {
        results[i] = 0; // Start count at 0

        // 4. Check against every string in the list
        for (int j = 0; j < stringList_count; j++) {
            // strcmp returns 0 if strings are identical
            if (strcmp(queries[i], stringList[j]) == 0) {
                results[i]++;
            }
        }
    }
    return results;
}

/*
 * The Main Function (Fixes your error)
 */
int main() {
    // --- 1. Read Input Strings (stringList) ---
    int n;
    scanf("%d", &n); // Read number of input strings

    // Allocate memory for the list of strings
    char** stringList = malloc(n * sizeof(char*));
    for (int i = 0; i < n; i++) {
        // Allocate space for each string (max length 20 + 1 for null terminator)
        stringList[i] = malloc(21 * sizeof(char));
        scanf("%s", stringList[i]);
    }

    // --- 2. Read Queries ---
    int q;
    scanf("%d", &q); // Read number of queries

    // Allocate memory for the list of queries
    char** queries = malloc(q * sizeof(char*));
    for (int i = 0; i < q; i++) {
        queries[i] = malloc(21 * sizeof(char));
        scanf("%s", queries[i]);
    }

    // --- 3. Call the Logic Function ---
    int result_count;
    int* res = matchingStrings(n, stringList, q, queries, &result_count);

    // --- 4. Print Results ---
    for (int i = 0; i < result_count; i++) {
        printf("%d\n", res[i]);
    }

    return 0;
}
