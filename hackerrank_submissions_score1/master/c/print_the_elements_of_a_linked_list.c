/*
 * Contest: Master
 * Challenge: Print the Elements of a Linked List
 * Language: c
 * Score: 1.0
 */


void printLinkedList(SinglyLinkedListNode* head) {
    // 1. Create a pointer to traverse the list (optional, can use 'head' directly)
    SinglyLinkedListNode* current = head;

    // 2. Loop until we reach the end of the list (NULL)
    while (current != NULL) {
        // 3. Print the data of the current node followed by a newline
        printf("%d\n", current->data);

        // 4. Move the pointer to the next node
        current = current->next;
    }
}

