/*
 * Contest: Master
 * Challenge: Tree: Inorder Traversal
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
void inOrder(struct node *root) {
    // 1. Base Case: If node is NULL, return
    if (root == NULL) {
        return;
    }

    // 2. Traverse Left Subtree
    inOrder(root->left);

    // 3. Visit Root (Print data)
    printf("%d ", root->data);

    // 4. Traverse Right Subtree
    inOrder(root->right);
}
