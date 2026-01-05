/*
 * Contest: Master
 * Challenge: Insert a node at the head of a linked list
 * Language: c
 * Score: 1.0
 */



SinglyLinkedListNode* insertNodeAtHead(SinglyLinkedListNode* llist, int data) {
    // 1. Allocate memory for the new node
    SinglyLinkedListNode* new_node = (SinglyLinkedListNode*)malloc(sizeof(SinglyLinkedListNode));

    // 2. Set the data for the new node
    new_node->data = data;

    // 3. Point the new node's next to the current head (llist)
    // If llist was NULL (empty list), new_node->next becomes NULL, which is correct.
    new_node->next = llist;

    // 4. Return the new node as the new head of the list
    return new_node;
}

