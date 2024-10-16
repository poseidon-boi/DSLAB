#include <stdio.h>
#include <stdlib.h>

/** A node of the tree */
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

int max(node* root) {
    for (; root -> right; root = root -> right);
    return root -> data;
}

/** Deletes a node from the BST
 * @param root The root of the BST
 * @param ele The element to delete
 * @param found Integer pointer storing whether the element is found
 * @return The updated root node of the BST
 */
node* delete(node* root, int ele, int* found) {
    if (!root) {
        *found = 0;
        return NULL;
    }
    if (ele < root -> data) {
        root -> left = delete(root -> left, ele, found);
        return root;
    }
    else if (ele > root -> data) {
        root -> right = delete(root -> right, ele, found);
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
    root -> left = delete(temp, ele1, found);
    return root;
}

/** Searches for the entered element in BST
 * @param root The root of the BST
 * @param ele The element to search for
 * @return 1 if found, 0 if not found
 */
int search(node* root, int ele) {
    if (!root)
        return 0;
    if (ele == root -> data)
        return 1;
    if (ele < root -> data)
        return search(root -> left, ele);
    return search(root -> right, ele);
}

/** Traverses and prints the elements in the BST in sorted order
 * @param root The root of the BST
 */
void traverse(node* root) {
    if (!root)
        return;
    traverse(root -> left);
    printf("%d ", root -> data);
    traverse(root -> right);
}

int main() {
    printf("1. Insert element\n2. Delete element\n"
           "3. Search for element\n4. Traverse\n"
           "5. Exit\nEnter choice: ");
    char ch;
    scanf(" %c", &ch);
    node* root = NULL;
    while (1) {
        int ele, found = 1;
        switch (ch) {
        case '1':
            printf("Enter element to insert: ");
            scanf("%d", &ele);
            root = insert(root, ele);
            break;
        case '2':
            printf("Enter element to delete: ");
            scanf("%d", &ele);
            delete(root, ele, &found);
            if (!found)
                printf("Element not found\n");
            break;
        case '3':
            printf("Enter element to search: ");
            scanf("%d", &ele);
            if (search(root, ele))
                printf("Element found\n");
            else
                printf("Element not found\n");
            break;
        case '4':
            traverse(root);
            printf("\n");
            break;
        case '5': return 0;
        default: printf("Invalid choice\n");
        }
        printf("Enter choice: ");
        scanf(" %c", &ch);
    }
    return 0;
}