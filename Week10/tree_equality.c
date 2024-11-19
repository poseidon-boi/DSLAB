#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

/** Checks whether the two entered trees are equal
 * @param root1 The root of the first binary tree
 * @param root2 The root of the second binary tree
 * @return 1 if equal, 0 if not equal
 */
int is_equal(node* root1, node* root2);

int main() {

    printf("1. Insert element into tree 1\n"
           "2. Insert element into tree 2\n"
           "3. Print tree 1\n"
           "4. Print tree 2\n"
           "5. Check for equality\n"
           "6. Exit\n");

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
        case 2:
            printf("Enter element to insert: ");
            if (!scanf("%d", &ele)) {
                int c;
                while ((c = getchar()) != '\n' && c != EOF);
                printf("Not a number\n");
                break;
            }
            if (ch == 1)
                tree1 = insert(tree1, ele);
            else
                tree2 = insert(tree2, ele);
            break;
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
        case 5:
            if (is_equal(tree1, tree2))
                printf("Trees are equal\n");
            else
                printf("Trees are not equal\n");
            break;
        case 6: return EXIT_SUCCESS;
        default: printf("Invalid choice\n");
        }

    }
    
}

int is_equal(node* root1, node* root2) {
    if (!root1 && !root2)
        return 1;
    if (!root1 || !root2)
        return 0;
    if (root1 -> data != root2 -> data)
        return 0;
    return (is_equal(root1 -> left, root2 -> left)
            && is_equal(root1 -> right, root2 -> right));
}