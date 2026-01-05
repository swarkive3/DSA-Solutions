/*
 * Contest: Master
 * Challenge: Cycle Detection
 * Language: c
 * Score: 1.0
 */



/*
 * Complete the has_cycle function below.
 *
 * For your reference:
 *
 * SinglyLinkedListNode {
 * int data;
 * SinglyLinkedListNode* next;
 * };
 *
 */
bool has_cycle(SinglyLinkedListNode* head) {
    // 1. Handle Edge Case: Empty list or single node cannot have a cycle
    if (head == NULL) {
        return false;
    }

    // 2. Initialize two pointers: 'slow' and 'fast'
    SinglyLinkedListNode* slow = head;
    SinglyLinkedListNode* fast = head;

    // 3. Traverse the list
    // 'fast' needs to check two steps ahead, so we must ensure 
    // fast and fast->next are not NULL.
    while (fast != NULL && fast->next != NULL) {
        
        // Move slow pointer one step
        slow = slow->next;
        
        // Move fast pointer two steps
        fast = fast->next->next;

        // 4. Check for collision
        // If the pointers meet, there is a cycle.
        if (slow == fast) {
            return true;
        }
    }

    // 5. If 'fast' reaches the end (NULL), there is no cycle.
    return false;
}

