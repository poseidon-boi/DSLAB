#include <stdio.h>
#include <stdlib.h>

/** Node of the singly linked list
 * @param data
 * @param next
 */
typedef struct node {
    /** The data stored in the node */
    int data;
    /** The pointer to the next node */
    struct node* next;
} node;

/** Inserts a node to the start of the linked list, like a push operation
 * @param list Pointer to pointer to head node
 * @param head The current node of the linked list
 * @param ele The element to insert
 */
void insert_tail(node** list, node* cur, int ele) {
    if (!cur) {
        cur = malloc(sizeof(*cur));
        cur -> next = NULL;
        cur -> data = ele;
        *list = cur;
        return;
    }
    if (!cur -> next) {
        node* insert = malloc(sizeof(*insert));
        insert -> data = ele;
        cur -> next = insert;
        return;
    }
    insert_tail(list, cur -> next, ele);
}

/** Traverses the list
 * @param head The head node of linked list
 */
void traverse(node* head) {
    if (head == NULL) {
        printf("\n");
        return;
    }
    printf("%d ", head -> data);
    traverse(head -> next);
}

int main() {
    printf("1. Insert into list\n2. Traverse list\n3. Exit\nEnter choice: ");
    int ch;
    scanf("%d", &ch);
    node** head = malloc(sizeof(*head));
    while (1) {
        int ele;
        switch(ch) {
            case 1:
                printf("Enter element to insert: ");
                scanf("%d", &ele);
                insert_tail(head, *head, ele);
                break;
            case 2:
                traverse(*head); break;
            case 3: return 0;
            default: printf("Invalid choice\n");
        }
        printf("Enter choice: ");
        scanf("%d", &ch);
    }
}
