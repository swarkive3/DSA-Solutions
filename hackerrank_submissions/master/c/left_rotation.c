/*
 * Contest: Master
 * Challenge: Left Rotation
 * Language: c
 * Score: 1.0
 */

#include <stdio.h>
#include <stdlib.h>

/*
 * The Logic Function
 * Note: result_count is a pointer where we store the size of the returned array.
 */
int* rotateLeft(int d, int arr_count, int* arr, int* result_count) {
    // 1. Set the size of the result array (same as input size)
    *result_count = arr_count;

    // 2. Allocate memory for the new rotated array
    int* rotated_arr = (int*)malloc(arr_count * sizeof(int));
    
    // Safety check for memory allocation
    if (rotated_arr == NULL) {
        return NULL;
    }

    // 3. Fill the new array using the modulo formula
    for (int i = 0; i < arr_count; i++) {
        // The value at new index 'i' comes from the old index '(i + d) % n'
        int old_index = (i + d) % arr_count;
        rotated_arr[i] = arr[old_index];
    }

    return rotated_arr;
}

/*
 * The Main Function (Driver Code)
 */
int main() {
    int n, d;

    // 1. Read n (array size) and d (rotations)
    // Validate input to avoid crashes
    if (scanf("%d %d", &n, &d) != 2) {
        return 0; 
    }

    // 2. Allocate memory for the input array
    int* arr = (int*)malloc(n * sizeof(int));
    if (arr == NULL) return 1; // Exit if allocation fails

    // 3. Read the array elements
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    // 4. Call the rotation function
    int result_count;
    int* result = rotateLeft(d, n, arr, &result_count);

    // 5. Print the result
    for (int i = 0; i < result_count; i++) {
        printf("%d", result[i]);
        
        // Print a space after every element except the last one
        if (i < result_count - 1) {
            printf(" ");
        }
    }
    printf("\n");

    // 6. Free allocated memory
    free(arr);
    free(result);

    return 0;
}
