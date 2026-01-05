/*
 * Contest: Master
 * Challenge: Array Manipulation
 * Language: c
 * Score: 1.0
 */

#include <stdio.h>
#include <stdlib.h>

/*
 * The Logic Function
 */
long arrayManipulation(int n, int queries_rows, int queries_columns, int** queries) {
    // 1. Create a difference array. 
    // We need size n + 2 because indices are 1-based and we access index 'b + 1'.
    // calloc initializes all elements to 0.
    long* arr = (long*)calloc(n + 2, sizeof(long));
    
    // Safety check
    if (arr == NULL) {
        return 0;
    }

    // 2. Process updates in O(1) time each
    for (int i = 0; i < queries_rows; i++) {
        int a = queries[i][0];
        int b = queries[i][1];
        int k = queries[i][2];

        // Add k at the starting index
        arr[a] += k;

        // Subtract k AFTER the ending index to stop the effect
        // If b is the last element (n), b+1 updates the (n+1)th index, which is safe due to size n+2
        if (b + 1 <= n) {
            arr[b + 1] -= k;
        } else {
             // Even if b+1 > n, we can store it at n+1 safely because we allocated n+2
             arr[b + 1] -= k; 
        }
    }

    // 3. Calculate Prefix Sums and find Maximum
    long max_value = 0;
    long current_sum = 0;

    for (int i = 1; i <= n; i++) {
        current_sum += arr[i];
        
        if (current_sum > max_value) {
            max_value = current_sum;
        }
    }

    // Free the temporary array
    free(arr);

    return max_value;
}

/*
 * The Main Function (Driver Code)
 */
int main() {
    int n, m;

    // 1. Read N (array size) and M (number of queries)
    if (scanf("%d %d", &n, &m) != 2) return 0;

    // 2. Allocate memory for the 2D queries array
    // We use a pointer-to-pointer to match the function signature
    int** queries = (int**)malloc(m * sizeof(int*));
    for (int i = 0; i < m; i++) {
        queries[i] = (int*)malloc(3 * sizeof(int));
        
        // Read a, b, and k for each query
        scanf("%d %d %d", &queries[i][0], &queries[i][1], &queries[i][2]);
    }

    // 3. Call the function
    long result = arrayManipulation(n, m, 3, queries);

    // 4. Print the result
    // Use %ld for long integers
    printf("%ld\n", result);

    // 5. Clean up memory
    for (int i = 0; i < m; i++) {
        free(queries[i]);
    }
    free(queries);

    return 0;
}
