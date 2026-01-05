/*
 * Contest: Master
 * Challenge: Inserting a Node Into a Sorted Doubly Linked List
 * Language: c
 * Score: 0.0
 */


DoublyLinkedListNode* sortedInsert(DoublyLinkedListNode* llist, int data) {
    // 1. Allocation: Create the new node manually
    DoublyLinkedListNode* newNode = malloc(sizeof(DoublyLinkedListNode));
    newNode->data = data;
    newNode->next = NULL;
    newNode->prev = NULL;

    // 2. Case: The list is empty
    // If list is empty, the new node is the head
    if (llist == NULL) {
        return newNode;
    }

    // 3. Case: Insert at the Head (beginning)
    // If new data is smaller than head, insert before head
    if (data <= llist->data) {
        newNode->next = llist;
        llist->prev = newNode;
        return newNode; // New node is the new head
    }

    // 4. Case: Insert in the Middle or End
    DoublyLinkedListNode* current = llist;

    // Traverse the list. Stop if we reach the last node 
    // OR if the *next* node's data is bigger than our new data.
    while (current->next != NULL && current->next->data < data) {
        current = current->next;
    }

    // We have found the node 'current' AFTER which we must insert 'newNode'
    newNode->next = current->next;
    newNode->prev = current;

    // If we are not at the very end, link the next node back to newNode
    if (current->next != NULL) {
        current->next->prev = newNode;
    }

    // Link current forward to newNode
    current->next = newNode;

    // 5. Return the original head
    return llist;
}
/*
 * Complete the 'sortedInsert' function below.
 *
 * The function is expected to return an INTEGER_DOUBLY_LINKED_LIST.
 * The function accepts following parameters:
 * 1. INTEGER_DOUBLY_LINKED_LIST llist
 * 2. INTEGER data
 */

/*
 * For your reference:
 *
 * DoublyLinkedListNode {
 * int data;
 * DoublyLinkedListNode* next;
 * DoublyLinkedListNode* prev;
 * };
 *
 */

DoublyLinkedListNode* sortedInsert(DoublyLinkedListNode* llist, int data) {
    // 1. Allocate memory for the new node
    DoublyLinkedListNode* newNode = (DoublyLinkedListNode*)malloc(sizeof(DoublyLinkedListNode));
    newNode->data = data;
    newNode->next = NULL;
    newNode->prev = NULL;

    // 2. Case: Empty List
    // If the list is empty, the new node becomes the unique head.
    if (llist == NULL) {
        return newNode;
    }

    // 3. Case: Insert at Head
    // If the new value is smaller than the current head, insert before head.
    if (data <= llist->data) {
        newNode->next = llist;
        llist->prev = newNode;
        return newNode; // New node becomes the new head
    }

    // 4. Case: Insert in Middle or Tail
    // We need to find the node 'current' AFTER which the new node belongs.
    DoublyLinkedListNode* current = llist;

    // Traverse while there is a next node AND the next node is smaller than our data.
    while (current->next != NULL && current->next->data < data) {
        current = current->next;
    }

    // Perform the insertion after 'current'
    newNode->next = current->next;
    newNode->prev = current;

    // If we are NOT at the tail, update the next node's back-pointer
    if (current->next != NULL) {
        current->next->prev = newNode;
    }

    // Link 'current' forward to the new node
    current->next = newNode;

    // 5. Return the original head
    return llist;
}

