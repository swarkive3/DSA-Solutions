/*
 * Contest: Master
 * Challenge: Insert a Node at the Tail of a Linked List
 * Language: c
 * Score: 1.0
 */


SinglyLinkedListNode* insertNodeAtTail(SinglyLinkedListNode* head, int data) {
    // 1. Allocate memory for the new node
    SinglyLinkedListNode* new_node = (SinglyLinkedListNode*)malloc(sizeof(SinglyLinkedListNode));
    
    // 2. Set data and ensure next is NULL (since it will be the tail)
    new_node->data = data;
    new_node->next = NULL;

    // 3. Handle the edge case: If the list is empty, new node is the head
    if (head == NULL) {
        return new_node;
    }

    // 4. Traverse to the end of the list
    SinglyLinkedListNode* current = head;
    while (current->next != NULL) {
        current = current->next;
    }

    // 5. Link the last node to the new node
    current->next = new_node;

    // 6. Return the original head of the list
    return head;
}

