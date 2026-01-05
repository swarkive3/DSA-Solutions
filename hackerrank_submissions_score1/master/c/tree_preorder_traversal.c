/*
 * Contest: Master
 * Challenge: Tree: Preorder Traversal
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
void preOrder( struct node *root) {


if (root == NULL) {
        return;
    }

    // 2. Visit Root: Print the data followed by a space
    printf("%d ", root->data);

    // 3. Traverse Left: Recursively visit the left subtree
    preOrder(root->left);

    // 4. Traverse Right: Recursively visit the right subtree
    preOrder(root->right);
}
