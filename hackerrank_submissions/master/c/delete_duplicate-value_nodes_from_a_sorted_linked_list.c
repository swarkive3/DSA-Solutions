/*
 * Contest: Master
 * Challenge: Delete duplicate-value nodes from a sorted linked list
 * Language: c
 * Score: 1.0
 */



/*
 * Complete the 'removeDuplicates' function below.
 *
 * The function is expected to return an INTEGER_SINGLY_LINKED_LIST.
 * The function accepts INTEGER_SINGLY_LINKED_LIST llist as parameter.
 */

SinglyLinkedListNode* removeDuplicates(SinglyLinkedListNode* llist) {
    // 1. Handle Edge Case: Empty List
    if (llist == NULL) {
        return NULL;
    }

    // 2. Initialize a pointer to traverse the list
    SinglyLinkedListNode* current = llist;

    // 3. Iterate as long as there is a current node AND a next node to compare
    while (current->next != NULL) {
        
        // 4. Check for Duplicate
        // Since the list is sorted, duplicates are always adjacent.
        if (current->data == current->next->data) {
            
            // A. Store the duplicate node temporarily so we can free it
            SinglyLinkedListNode* duplicate = current->next;
            
            // B. Re-link: Skip the duplicate and point to the node after it
            current->next = duplicate->next;
            
            // C. Free the memory of the duplicate node
            free(duplicate);
            
            // D. CRITICAL: Do NOT advance 'current' here.
            // The *new* next node might also be a duplicate (e.g., 2 -> 2 -> 2).
            // We need to check 'current' against the new neighbor in the next iteration.
            
        } else {
            // 5. No duplicate found, move to the next node
            current = current->next;
        }
    }

    // 6. Return the head of the modified list
    return llist;
}

