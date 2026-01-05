/*
 * Contest: Master
 * Challenge: Dynamic Array
 * Language: c
 * Score: 1.0
 */

#include <stdio.h>
#include <stdlib.h>

/*
 * The Logic Function
 * result_count is a pointer to store the size of the returned array.
 */
int* dynamicArray(int n, int queries_rows, int queries_columns, int** queries, int* result_count) {
    // 1. Initialize the main structure (Array of Pointers)
    // 'arr' will point to 'n' different arrays.
    int** arr = (int**)malloc(n * sizeof(int*));
    
    // 'counts' will keep track of how many elements are in each sub-array
    int* counts = (int*)calloc(n, sizeof(int)); 

    // Initialize each sub-array to NULL (empty) initially
    for (int i = 0; i < n; i++) {
        arr[i] = NULL;
    }

    // 2. Prepare the results array
    // In the worst case, every query is type 2, so we allocate max size.
    int* results = (int*)malloc(queries_rows * sizeof(int));
    int result_idx = 0;
    
    int lastAnswer = 0;

    // 3. Process Queries
    for (int i = 0; i < queries_rows; i++) {
        int type = queries[i][0];
        int x = queries[i][1];
        int y = queries[i][2];

        // Calculate the index using the XOR formula provided
        int idx = (x ^ lastAnswer) % n;

        if (type == 1) {
            // --- Query Type 1: Append y ---
            
            // Increment the count for this specific sequence
            counts[idx]++;
            
            // Resize the specific sequence to hold one more integer
            // realloc preserves existing data and adds space
            arr[idx] = (int*)realloc(arr[idx], counts[idx] * sizeof(int));
            
            // Add the new value at the end
            arr[idx][counts[idx] - 1] = y;

        } else if (type == 2) {
            // --- Query Type 2: Find Value ---
            
            // Determine which element to pick
            int size = counts[idx];
            int value_index = y % size;
            
            // Update lastAnswer
            lastAnswer = arr[idx][value_index];
            
            // Add to results
            results[result_idx++] = lastAnswer;
        }
    }

    // 4. Update the output size variable
    *result_count = result_idx;

    // 5. Clean up temporary memory (Optional but good practice)
    for(int i=0; i<n; i++) {
        free(arr[i]);
    }
    free(arr);
    free(counts);

    return results;
}

/*
 * The Main Function (Driver Code)
 */
int main() {
    int n, q;
    
    // 1. Read N and Q
    if (scanf("%d %d", &n, &q) != 2) return 0;

    // 2. Read Queries
    int** queries = (int**)malloc(q * sizeof(int*));
    for (int i = 0; i < q; i++) {
        queries[i] = (int*)malloc(3 * sizeof(int));
        scanf("%d %d %d", &queries[i][0], &queries[i][1], &queries[i][2]);
    }

    // 3. Call Function
    int result_count;
    int* results = dynamicArray(n, q, 3, queries, &result_count);

    // 4. Print Results
    for (int i = 0; i < result_count; i++) {
        printf("%d\n", results[i]);
    }

    // 5. Cleanup
    for(int i=0; i<q; i++) free(queries[i]);
    free(queries);
    free(results);

    return 0;
}
