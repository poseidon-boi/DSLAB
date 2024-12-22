#include <stdio.h>
#include <stdlib.h>

/** A node of the tree
 * @param data
 * @param right
 * @param left
 */
typedef struct node {
    /** The data in the node */
    int data;
    /** The right child of the node */
    struct node* right;
    /** The left child of the node */
    struct node* left;
} node;

/** Inserts an element into the BST
 * @param root The root of the BST
 * @param ele The element to insert
 * @return The updated root node
 */
node* insert(node* root, int ele);

/** Finds the maximum element in a BST
 * @param root The root of the BST
 * @return The maximum element of the BST
 */
static int max(node* root);

/** Deletes a node from the BST
 * @param root The root of the BST
 * @param ele The element to delete
 * @param found Integer pointer storing whether the element is found
 * @return The updated root node of the BST
 */
node* delete_ele(node* root, int ele, int* found);

/** Searches for the entered element in BST
 * @param root The root of the BST
 * @param ele The element to search for
 * @return 1 if found, 0 if not found
 */
int search(node* root, int ele);

/** Traverses and prints the elements in the BST in sorted order
 * @param root The root of the BST
 */
void traverse_inorder(node* root);

int main() {
    printf("1. Insert element\n2. Delete element\n"
           "3. Search for element\n4. Traverse\n"
           "5. Exit\nEnter choice: ");
    char ch;
    scanf(" %c", &ch);
    node* root = NULL;
    while (1) {
        int ele, found = 1, error = 0;
        switch (ch) {
        case '1':
            printf("Enter element to insert: ");
            if (!scanf("%d", &ele)) {
                int c;
                while ((c = getchar()) != '\n' && c != EOF);
                error = 1;
                break;
            }
            root = insert(root, ele);
            break;
        case '2':
            printf("Enter element to delete: ");
            if (!scanf("%d", &ele)) {
                int c;
                while ((c = getchar()) != '\n' && c != EOF);
                error = 1;
                break;
            }
            root = delete_ele(root, ele, &found);
            if (!found)
                printf("Element not found\n");
            break;
        case '3':
            printf("Enter element to search: ");
            if (!scanf("%d", &ele)) {
                int c;
                while ((c = getchar()) != '\n' && c != EOF);
                error = 1;
                break;
            }
            if (search(root, ele))
                printf("Element found\n");
            else
                printf("Element not found\n");
            break;
        case '4':
            traverse_inorder(root);
            printf("\n");
            break;
        case '5': return 0;
        default: printf("Invalid choice\n");
        }
        if (error)
            printf("Operation failed\n");
        printf("Enter choice: ");
        scanf(" %c", &ch);
    }
}

node* insert(node* root, int ele) {
    if (!root) {
        root = malloc(sizeof(*root));
        root -> data = ele;
        root -> left = root -> right = NULL;
        return root;
    }
    if (ele == root -> data)
        return root;
    if (ele < root -> data)
        root -> left = insert(root -> left, ele);
    else
        root -> right = insert(root -> right, ele);
    return root;
}

static int max(node* root) {
    for (; root -> right; root = root -> right);
    return root -> data;
}

node* delete_ele(node* root, int ele, int* found) {
    if (!root) {
        *found = 0;
        return NULL;
    }
    if (ele < root -> data) {
        root -> left = delete_ele(root -> left, ele, found);
        return root;
    }
    if (ele > root -> data) {
        root -> right = delete_ele(root -> right, ele, found);
        return root;
    }
    if (!root -> left && !root -> right) {
        free(root);
        return NULL;
    }
    if (!root -> right || !root -> left) {
        node* temp = root;
        if (!root -> left)
            root = root -> right;
        if (!root -> right)
            root = root -> left;
        free(temp);
        return root;
    }
    node* temp = root -> left;
    int ele1 = root -> data = max(temp);
    root -> left = delete_ele(temp, ele1, found);
    return root;
}

int search(node* root, int ele) {
    if (!root)
        return 0;
    if (ele == root -> data)
        return 1;
    if (ele < root -> data)
        return search(root -> left, ele);
    return search(root -> right, ele);
}

void traverse_inorder(node* root) {
    if (!root)
        return;
    traverse_inorder(root -> left);
    printf("%d ", root -> data);
    traverse_inorder(root -> right);
}