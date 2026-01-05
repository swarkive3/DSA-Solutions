/*
 * Contest: Master
 * Challenge: Reverse a linked list
 * Language: c
 * Score: 1.0
 */



/*
 * Complete the 'reverse' function below.
 *
 * The function is expected to return an INTEGER_SINGLY_LINKED_LIST.
 * The function accepts INTEGER_SINGLY_LINKED_LIST llist as parameter.
 */

SinglyLinkedListNode* reverse(SinglyLinkedListNode* llist) {
    // 1. Initialize three pointers
    SinglyLinkedListNode* prev = NULL;
    SinglyLinkedListNode* current = llist;
    SinglyLinkedListNode* next_node = NULL;

    // 2. Iterate through the list
    while (current != NULL) {
        // Store the next node so we don't lose the rest of the list
        next_node = current->next;

        // REVERSE the pointer: Point current node backwards to 'prev'
        current->next = prev;

        // Move 'prev' and 'current' one step forward
        prev = current;
        current = next_node;
    }

    // 3. Return the new head
    // At the end of the loop, 'current' is NULL, and 'prev' is the new head.
    return prev;
}

