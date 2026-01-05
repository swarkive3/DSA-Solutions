/*
 * Contest: Master
 * Challenge: 2D Array - DS
 * Language: c
 * Score: 1.0
 */

#include <stdio.h>
#include <stdlib.h>

/*
 * The Logic Function
 */
int hourglassSum(int arr_rows, int arr_columns, int** arr) {
    // Initialize to a low negative number because sums can be negative
    int max_sum = -100;

    // Loop through rows (stop 2 before the end)
    for (int i = 0; i < arr_rows - 2; i++) {
        // Loop through columns (stop 2 before the end)
        for (int j = 0; j < arr_columns - 2; j++) {
            
            // Calculate the sum of the hourglass pattern
            int current_sum = arr[i][j] + arr[i][j+1] + arr[i][j+2] +
                              arr[i+1][j+1] +
                              arr[i+2][j] + arr[i+2][j+1] + arr[i+2][j+2];
            
            // Update max_sum if we found a larger sum
            if (current_sum > max_sum) {
                max_sum = current_sum;
            }
        }
    }
    return max_sum;
}

/*
 * The Main Function (Fixes your error)
 */
int main() {
    // 1. Allocate memory for the 6x6 2D array
    int** arr = malloc(6 * sizeof(int*));

    for (int i = 0; i < 6; i++) {
        arr[i] = malloc(6 * sizeof(int));
        
        // 2. Read the 6 integers for this row
        for (int j = 0; j < 6; j++) {
            scanf("%d", &arr[i][j]);
        }
    }

    // 3. Call the function
    int result = hourglassSum(6, 6, arr);

    // 4. Print the final result
    printf("%d\n", result);

    return 0;
}
