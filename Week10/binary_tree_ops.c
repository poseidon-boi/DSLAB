#include <stdio.h>
#include <stdlib.h>

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

int main() {
    printf("1. Insert element\n2. Print tree\n3. Traverse inorder\n"
           "4. Traverse postorder\n5. Traverse preorder\n"
           "6. Print parent\n7. Print depth\n8. Print ancestors\n"
           "9. Count leaf nodes\n10. Exit\nEnter choice: ");
    int ch;
    if (!scanf("%d", &ch)) {
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        ch = 11;
    }
    node* root = NULL;
    while (1) {
        int ele, found = 1, error = 0;
        switch (ch) {
        case 1:
            printf("Enter element to insert: ");
            if (!scanf("%d", &ele)) {
                while (getchar() != '\n');
                error = 1;
                break;
            }
            root = insert(root, ele);
            break;
        case 2: print_tree(root, 0); break;
        case 3:
            inorder(root);
            printf("\n");
            break;
        case 4:
            postorder(root);
            printf("\n");
            break;
        case 5:
            preorder(root);
            printf("\n");
            break;
        case 6:
            printf("Enter element: ");
            if (!scanf("%d", &ele)) {
                int c;
                while ((c = getchar()) != '\n' && c != EOF);
                error = 1;
                break;
            }
            found = print_parent(root, ele);
            if (found)
                printf("\n");
            break;
        case 7: 
            printf("Depth is: %d\n", depth(root, 0));
            break;
        case 8:
            printf("Enter element: ");
            if (!scanf("%d", &ele)) {
                int c;
                while ((c = getchar()) != '\n' && c != EOF);
                error = 1;
                break;
            }
            found = print_ancestors(root, ele);
            if (found)
                printf("\n");
            break;
        case 9:
            printf("Leaf nodes: %d\n", leaves(root));
            break;
        case 10: return 0;
        default: printf("Invalid choice\n");
        }
        if (!found)
            printf("Element not found\n");
        if (error)
            printf("Operation failed\n");
        printf("Enter choice: ");
        if (!scanf("%d", &ch)) {
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            ch = 11;
        }
    }
}

void inorder(node* root) {
    if (!root)
        return;
    inorder(root -> left);
    printf("%d ", root -> data);
    inorder(root -> right);
}

void postorder(node* root) {
    if (!root)
        return;
    postorder(root -> left);
    postorder(root -> right);
    printf("%d ", root -> data);
}

void preorder(node* root) {
    if (!root)
        return;
    printf("%d ", root -> data);
    preorder(root -> left);
    preorder(root -> right);
}

int print_parent(node* root, int ele) {
    if (!root)
        return 0;
    if (root)
        if (root -> data == ele)
            return 1;
    int found1 = 0, found2 = 0;
    if (root -> left) {
        if (root -> left -> data == ele) {
            printf("%d ", root -> data);
            return 1;
        }
        else
            found1 = print_parent(root -> left, ele);
    }
    if (root -> right) {
        if (root -> right -> data == ele) {
            printf("%d ", root -> data);
            return 1;
        }
        else
            found2 = print_parent(root -> right, ele);
    }
    return found1 || found2;
}

int depth(node* root, int curdepth) {
    if (!root)
        return curdepth - 1;
    int ldepth, rdepth;
    ldepth = depth(root -> left, curdepth + 1);
    rdepth = depth(root -> right, curdepth + 1);
    return (ldepth > rdepth)?ldepth:rdepth;
}

int print_ancestors(node* root, int ele) {
    if (!root)
        return 0;
    if (root)
        if (root -> data == ele)
            return 1;
    if (root -> left) {
        int found = print_ancestors(root -> left, ele);
        if (found) {
            printf("%d ", root -> data);
            return 1;
        }
    }
    if (root -> right) {
        int found = print_ancestors(root -> right, ele);
        if (found) {
            printf("%d ", root -> data);
            return 1;
        }
    }
    return 0;
}

int leaves(node* root) {
    if (!root)
        return 0;
    int lleaves, rleaves;
    lleaves = leaves(root -> left);
    rleaves = leaves(root -> right);
    if (lleaves + rleaves == 0)
        return 1;
    else
        return lleaves + rleaves;
}

node* insert(node* root, int ele) {
    if (!root) {
        root = malloc(sizeof(*root));
        root -> left = root -> right = NULL;
        root -> data = ele;
        return root;
    }
    node* temp;
    if (!root -> left || !root -> right) {
        temp = malloc(sizeof(*temp));
        temp -> data = ele;
        temp -> left = temp -> right = NULL;
    }
    if (!root -> left) {
        root -> left = temp;
        return root;
    }
    if (!root -> right) {
        root -> right = temp;
        return root;
    }
    if (leaves(root -> left) <= leaves(root -> right))
        insert(root -> left, ele);
    else
        insert(root -> right, ele);
    return root;
}

void print_tree(node* root, int curdepth) {
    if (!root)
        return;
    print_tree(root -> right, curdepth + 1);
    for (int i = 0; i < curdepth; i++)
        printf("\t");
    printf("%d\n", root -> data);
    print_tree(root -> left, curdepth + 1);
}