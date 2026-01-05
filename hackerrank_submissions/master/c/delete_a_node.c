/*
 * Contest: Master
 * Challenge: Delete a Node
 * Language: c
 * Score: 1.0
 */



/*
 * Complete the 'deleteNode' function below.
 *
 * The function is expected to return an INTEGER_SINGLY_LINKED_LIST.
 * The function accepts following parameters:
 * 1. INTEGER_SINGLY_LINKED_LIST llist
 * 2. INTEGER position
 */

SinglyLinkedListNode* deleteNode(SinglyLinkedListNode* llist, int position) {
    // 1. Handle Edge Case: Empty List
    if (llist == NULL) {
        return NULL;
    }

    // 2. Handle Case: Deleting the Head (Position 0)
    if (position == 0) {
        SinglyLinkedListNode* temp = llist;
        // Move head to the next node
        llist = llist->next;
        // Free the memory of the old head
        free(temp);
        return llist;
    }

    // 3. Traverse to the predecessor (node before the one to delete)
    SinglyLinkedListNode* current = llist;
    for (int i = 0; i < position - 1; i++) {
        current = current->next;
    }

    // 4. Identify the node to be deleted
    SinglyLinkedListNode* node_to_delete = current->next;

    // 5. Relink: Skip over the node_to_delete
    current->next = node_to_delete->next;

    // 6. Free the memory of the deleted node
    free(node_to_delete);

    // 7. Return the head of the list
    return llist;
}

