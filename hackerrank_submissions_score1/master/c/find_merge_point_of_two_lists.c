/*
 * Contest: Master
 * Challenge: Find Merge Point of Two Lists
 * Language: c
 * Score: 1.0
 */


/*
 * Complete the findMergeNode function below.
 *
 * For your reference:
 *
 * SinglyLinkedListNode {
 * int data;
 * SinglyLinkedListNode* next;
 * };
 *
 */
int findMergeNode(SinglyLinkedListNode* head1, SinglyLinkedListNode* head2) {
    // 1. Initialize two pointers, one for each list head.
    SinglyLinkedListNode* current1 = head1;
    SinglyLinkedListNode* current2 = head2;

    // 2. Traverse both lists.
    // The loop continues until the two pointers meet at the same node.
    while (current1 != current2) {
        
        // 3. Switch tracks at the end.
        // If current1 reaches the end (NULL), jump to the head of list 2.
        // Otherwise, move to the next node.
        if (current1 == NULL) {
            current1 = head2;
        } else {
            current1 = current1->next;
        }

        // Similarly for current2:
        // If current2 reaches the end (NULL), jump to the head of list 1.
        // Otherwise, move to the next node.
        if (current2 == NULL) {
            current2 = head1;
        } else {
            current2 = current2->next;
        }
    }

    // 4. Return the data of the merge node.
    // When the loop breaks, current1 == current2, which is the merge point.
    return current1->data;
}

