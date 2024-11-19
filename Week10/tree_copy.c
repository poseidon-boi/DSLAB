#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

/** Returns a copy of the given binary tree
 * @param root The root node of the entered binary tree
 * @return The root node of the copied binary tree
 */
node* copy_tree(node* root);

int main() {

    printf("1. Insert element into tree\n"
           "2. Copy tree\n"
           "3. Print original tree\n"
           "4. Print copied tree\n"
           "5. Exit\n");

    node* tree1, *tree2;
    tree1 = tree2 = NULL;

    while (1) {

        printf("Enter choice: ");
        int ch, ele;
        if (!scanf("%d", &ch)) {
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            ch = 7;
        }

        switch (ch)
        {
        case 1:
            printf("Enter element to insert: ");
            if (!scanf("%d", &ele)) {
                int c;
                while ((c = getchar()) != '\n' && c != EOF);
                printf("Not a number\n");
                break;
            }
            tree1 = insert(tree1, ele);
            break;
        case 2: tree2 = copy_tree(tree1); break;
        case 3:
            if (!tree1)
                printf("NULL\n");
            print_tree(tree1, 0);
            break;
        case 4:
            if (!tree2)
                printf("NULL\n");
            print_tree(tree2, 0);
            break;
        case 5: return EXIT_SUCCESS;
        default: printf("Invalid choice\n");
        }

    }
    
}

node* copy_tree(node* root) {
    if (!root)
        return NULL;
    node* rootcopy = malloc(sizeof(*rootcopy));
    rootcopy -> data = root -> data;
    rootcopy -> left = copy_tree(root -> left);
    rootcopy -> right = copy_tree(root -> right);
    return rootcopy;
}