/*
 * Contest: Master
 * Challenge: Print in Reverse
 * Language: c
 * Score: 1.0
 */



/*
 * Complete the 'reversePrint' function below.
 *
 * The function accepts INTEGER_SINGLY_LINKED_LIST llist as parameter.
 */

void reversePrint(SinglyLinkedListNode* llist) {
    // 1. Base Case: If the current node is NULL, we've reached the end.
    // Stop recursion and return.
    if (llist == NULL) {
        return;
    }

    // 2. Recursive Step: Call the function with the next node first.
    // This effectively travels to the end of the list *before* printing anything.
    reversePrint(llist->next);

    // 3. Action: Print the current node's data.
    // Because this happens after the recursive call returns, the last node
    // prints first, then the second-to-last, etc.
    printf("%d\n", llist->data);
}
