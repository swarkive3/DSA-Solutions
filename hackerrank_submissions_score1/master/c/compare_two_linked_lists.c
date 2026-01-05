/*
 * Contest: Master
 * Challenge: Compare two linked lists
 * Language: c
 * Score: 1.0
 */



/*
 * Complete the compare_lists function below.
 *
 * For your reference:
 *
 * SinglyLinkedListNode {
 * int data;
 * SinglyLinkedListNode* next;
 * };
 *
 */
bool compare_lists(SinglyLinkedListNode* head1, SinglyLinkedListNode* head2) {
    // 1. Traverse both lists simultaneously (Lockstep)
    while (head1 != NULL && head2 != NULL) {
        // 2. Compare Data: If values differ, lists are not identical.
        if (head1->data != head2->data) {
            return false;
        }

        // 3. Advance Pointers: Move both to the next node.
        head1 = head1->next;
        head2 = head2->next;
    }

    // 4. Check Lengths: After the loop, BOTH pointers must be NULL.
    // If one is NULL and the other isn't, lengths differ.
    if (head1 == NULL && head2 == NULL) {
        return true;
    } else {
        return false;
    }
}

