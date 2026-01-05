/*
 * Contest: Master
 * Challenge: Queue using Two Stacks
 * Language: c
 * Score: 1.0
 */

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

// Define maximum size based on constraints (10^5 queries)
#define MAX_SIZE 100005

// Stack 1: For Enqueue operations
int stack_in[MAX_SIZE];
int top_in = -1;

// Stack 2: For Dequeue/Print operations
int stack_out[MAX_SIZE];
int top_out = -1;

// Helper: Move elements from input stack to output stack
// This reverses the order (LIFO -> FIFO)
void shift_stacks() {
    if (top_out == -1) {
        while (top_in != -1) {
            stack_out[++top_out] = stack_in[top_in--];
        }
    }
}

int main() {
    int q;
    // Read number of queries
    if (scanf("%d", &q) != 1) return 0;

    int type, x;
    while (q--) {
        scanf("%d", &type);

        if (type == 1) {
            // --- Enqueue ---
            // Read value x and push to input stack
            scanf("%d", &x);
            stack_in[++top_in] = x;
        } 
        else if (type == 2) {
            // --- Dequeue ---
            // Ensure output stack has elements, then pop
            shift_stacks();
            if (top_out != -1) {
                top_out--;
            }
        } 
        else if (type == 3) {
            // --- Print Front ---
            // Ensure output stack has elements, then print top
            shift_stacks();
            if (top_out != -1) {
                printf("%d\n", stack_out[top_out]);
            }
        }
    }
    
    return 0;
}
