/*
 * Contest: Master
 * Challenge: Tree: Level Order Traversal
 * Language: c
 * Score: 1.0
 */



/*
struct node {
    int data;
    struct node *left;
    struct node *right;
};
*/

void levelOrder(struct node *root) {
    // 1. Handle edge case: empty tree
    if (root == NULL) {
        return;
    }

    // 2. Create a generic queue using an array of pointers
    // The constraint is 500 nodes, so size 505 is safe.
    struct node* queue[505]; 
    int front = 0;
    int rear = 0;

    // 3. Enqueue the root node
    queue[rear] = root;
    rear++;

    // 4. Loop while the queue is not empty
    while (front < rear) {
        // Dequeue the current node
        struct node* current = queue[front];
        front++;

        // Print the data followed by a space
        printf("%d ", current->data);

        // Enqueue Left Child if it exists
        if (current->left != NULL) {
            queue[rear] = current->left;
            rear++;
        }

        // Enqueue Right Child if it exists
        if (current->right != NULL) {
            queue[rear] = current->right;
            rear++;
        }
    }
}
