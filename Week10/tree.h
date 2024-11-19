#ifndef TREE_H
#define TREE_H

/** A node of the tree
 * @param data
 * @param left
 * @param right
 */
typedef struct node {
    /** The data in the node */
    int data;
    /** The right child of the node */
    struct node* right;
    /** The left child of the node */
    struct node* left;
} node;

/** Traverses and prints the elements in the binary tree inorder
 * @param root The root of the binary tree
 */
void inorder(node* root);

/** Traverses and prints the elements in the binary tree postorder
 * @param root The root of the binary tree
 */
void postorder(node* root);

/** Traverses and prints the elements in the binary tree preorder
 * @param root The root of the binary tree
 */
void preorder(node* root);

/** Prints the parent of the entered element in the binary tree,
 *  prints nothing if element is not found
 * @param root The root of the binary tree
 * @param ele The element to print the parent of
 * @return 0 if the element is not found in the tree, 1 if found
 */
int print_parent(node* root, int ele);

/** Returns the depth of the binary tree
 * @param root The root of the binary tree
 * @param curdepth The current depth of the binary tree
 * @return The depth of the binary tree
 */
int depth(node* root, int curdepth);

/** Prints the ancestors of the entered element in the binary tree
 * @param root The root of the binary tree
 * @param ele The element to print the ancestors of
 * @return 0 if the element is not found in the tree, 1 if found
 */
int print_ancestors(node* root, int ele);

/** Returns the number of leaf nodes in the binary tree
 * @param root The root of the binary tree
 * @return The number of leaf nodes in the binary tree
 */
int leaves(node* root);

/** Inserts an element into the binary tree
 * @param root The root of the binary tree
 * @param ele The element to insert
 * @return The updated root node of the binary tree(useful during first insert)
 */
node* insert(node* root, int ele);

/** Prints the tree horizontally
 * @param root The root of the binary tree
 * @param depth The current depth of the root
 */
void print_tree(node* root, int curdepth);

#endif