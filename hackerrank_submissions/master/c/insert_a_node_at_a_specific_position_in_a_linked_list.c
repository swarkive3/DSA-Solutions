/*
 * Contest: Master
 * Challenge: Insert a node at a specific position in a linked list
 * Language: c
 * Score: 1.0
 */



/*
 * Complete the 'insertNodeAtPosition' function below.
 *
 * The function is expected to return an INTEGER_SINGLY_LINKED_LIST.
 * The function accepts following parameters:
 * 1. INTEGER_SINGLY_LINKED_LIST llist
 * 2. INTEGER data
 * 3. INTEGER position
 */

SinglyLinkedListNode* insertNodeAtPosition(SinglyLinkedListNode* llist, int data, int position) {
    // 1. Allocate memory for the new node
    SinglyLinkedListNode* new_node = (SinglyLinkedListNode*)malloc(sizeof(SinglyLinkedListNode));
    new_node->data = data;
    new_node->next = NULL;

    // 2. Handle Edge Case: Inserting at the head (Position 0)
    // If position is 0, the new node becomes the new head.
    if (position == 0) {
        new_node->next = llist;
        return new_node;
    }

    // 3. Traverse to the node just BEFORE the desired position
    // We need to stop at index (position - 1).
    SinglyLinkedListNode* current = llist;
    for (int i = 0; i < position - 1; i++) {
        current = current->next;
    }

    // 4. Perform the insertion
    // Point the new node's next to the current node's next
    new_node->next = current->next;
    
    // Update the current node's next to point to the new node
    current->next = new_node;

    // 5. Return the original head of the list
    return llist;
}

