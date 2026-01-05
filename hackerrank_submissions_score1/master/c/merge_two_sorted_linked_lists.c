/*
 * Contest: Master
 * Challenge: Merge two sorted linked lists
 * Language: c
 * Score: 1.0
 */



/*
 * Complete the mergeLists function below.
 *
 * For your reference:
 *
 * SinglyLinkedListNode {
 * int data;
 * SinglyLinkedListNode* next;
 * };
 *
 */
SinglyLinkedListNode* mergeLists(SinglyLinkedListNode* head1, SinglyLinkedListNode* head2) {
    // 1. Base Cases: If one list is empty, return the other.
    if (head1 == NULL) {
        return head2;
    }
    if (head2 == NULL) {
        return head1;
    }

    // 2. Determine the starting node (head of the merged list)
    // We want the smaller value to be the head.
    SinglyLinkedListNode* mergedHead = NULL;
    if (head1->data <= head2->data) {
        mergedHead = head1;
        head1 = head1->next;
    } else {
        mergedHead = head2;
        head2 = head2->next;
    }

    // 3. Initialize a pointer to build the new list
    SinglyLinkedListNode* current = mergedHead;

    // 4. Traverse both lists
    while (head1 != NULL && head2 != NULL) {
        // Compare data and link the smaller node to 'current->next'
        if (head1->data <= head2->data) {
            current->next = head1;
            head1 = head1->next;
        } else {
            current->next = head2;
            head2 = head2->next;
        }
        // Advance the 'current' pointer
        current = current->next;
    }

    // 5. Attach the remaining elements
    // One list will finish before the other. We simply link the rest
    // of the non-empty list to the end of our merged list.
    if (head1 == NULL) {
        current->next = head2;
    } else {
        current->next = head1;
    }

    // 6. Return the head of the merged list
    return mergedHead;
}

