/*
 * Contest: Master
 * Challenge: Sparse Arrays
 * Language: c
 * Score: 0.0
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Complete the 'matchingStrings' function below.
 *
 * The function is expected to return an INTEGER_ARRAY.
 * The function accepts following parameters:
 * 1. STRING_ARRAY stringList (The list of input strings)
 * 2. STRING_ARRAY queries (The strings to search for)
 */

int* matchingStrings(int stringList_count, char** stringList, int queries_count, char** queries, int* result_count) {
    // 1. Tell the caller how big the returned array will be
    // The result array size is always equal to the number of queries.
    *result_count = queries_count;

    // 2. Allocate memory for the result array
    int* results = (int*)malloc(queries_count * sizeof(int));
    if (results == NULL) {
        return NULL; // Safety check
    }

    // 3. Loop through every query string
    for (int i = 0; i < queries_count; i++) {
        // Initialize the count for the current query to 0
        results[i] = 0;

        // 4. Scan the entire stringList to find matches
        for (int j = 0; j < stringList_count; j++) {
            
            // strcmp returns 0 if the strings are exactly the same
            if (strcmp(queries[i], stringList[j]) == 0) {
                results[i]++;
            }
        }
    }

    return results;
}
