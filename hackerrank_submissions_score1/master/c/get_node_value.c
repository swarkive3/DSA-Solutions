/*
 * Contest: Master
 * Challenge: Get Node Value
 * Language: c
 * Score: 1.0
 */



/*
 * Complete the 'getNode' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 * 1. INTEGER_SINGLY_LINKED_LIST llist
 * 2. INTEGER positionFromTail
 */

int getNode(SinglyLinkedListNode* llist, int positionFromTail) {
    // 1. Initialize two pointers: 'slow' and 'fast' both pointing to head
    SinglyLinkedListNode* slow = llist;
    SinglyLinkedListNode* fast = llist;

    // 2. Move the 'fast' pointer forward by 'positionFromTail' steps
    // This creates a gap of exactly 'positionFromTail' nodes between fast and slow.
    for (int i = 0; i < positionFromTail; i++) {
        fast = fast->next;
    }

    // 3. Move both pointers forward simultaneously until 'fast' reaches the last node
    // When 'fast' is at the tail (index N-1), 'slow' will be at (N-1 - positionFromTail).
    while (fast->next != NULL) {
        fast = fast->next;
        slow = slow->next;
    }

    // 4. Return the data at the 'slow' pointer
    return slow->data;
}
