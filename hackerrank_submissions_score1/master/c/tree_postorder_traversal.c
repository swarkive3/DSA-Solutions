/*
 * Contest: Master
 * Challenge: Tree: Postorder Traversal
 * Language: c
 * Score: 1.0
 */



/* you only have to complete the function given below.  
node is defined as  

struct node {
    
    int data;
    struct node *left;
    struct node *right;
  
};

*/
void postOrder(struct node *root) {
    // 1. Base Case: If the node is NULL, stop recursion
    if (root == NULL) {
        return;
    }

    // 2. Traverse Left Subtree
    postOrder(root->left);

    // 3. Traverse Right Subtree
    postOrder(root->right);

    // 4. Visit the Root (Print data followed by a space)
    printf("%d ", root->data);
}

