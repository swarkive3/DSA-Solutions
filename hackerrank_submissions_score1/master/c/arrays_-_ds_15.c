/*
 * Contest: Master
 * Challenge: Arrays - DS
 * Language: c
 * Score: 1.0
 */

#include <stdio.h>
#include <stdlib.h>

/*
 * Complete the 'reverseArray' function below.
 *
 * The function is expected to return an INTEGER_ARRAY.
 * The function accepts INTEGER_ARRAY a as parameter.
 */

// Note: result_count is a pointer that tells the main function how big the returned array is.
int* reverseArray(int a_count, int* a, int* result_count) {
    // 1. Set the size of the result array
    *result_count = a_count;

    // 2. Allocate memory for the new reversed array
    int* reversed_a = (int*)malloc(a_count * sizeof(int));

    // 3. Check if memory allocation failed
    if (reversed_a == NULL) {
        return NULL;
    }

    // 4. Fill the new array in reverse order
    for (int i = 0; i < a_count; i++) {
        // Place the last element of 'a' into the first position of 'reversed_a'
        reversed_a[i] = a[a_count - 1 - i];
    }

    return reversed_a;
}

// Driver code to test the function (similar to what Hackerrank uses internally)
int main() {
    int n;
    
    // Read the size of the array
    if (scanf("%d", &n) != 1) return 0;

    // Allocate memory for the input array
    int* arr = (int*)malloc(n * sizeof(int));
    
    // Read the array elements
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    // Variable to store the size of the result array
    int result_count;
    
    // Call the function
    int* res = reverseArray(n, arr, &result_count);

    // Print the result
    for (int i = 0; i < result_count; i++) {
        printf("%d", res[i]);
        
        // Add a space only if it's not the last element
        if (i != result_count - 1) {
            printf(" ");
        }
    }
    printf("\n");

    // Free allocated memory
    free(arr);
    free(res);

    return 0;
}
