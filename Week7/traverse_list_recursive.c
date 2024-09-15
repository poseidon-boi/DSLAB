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
 * @param head The head node of the linked list
 * @param ele The element to insert
 * @return Returns the updated head node of the linked list
 */
node* insert_start(node* head, int ele) {
    if (!head) {
        head = malloc(sizeof(*head));
        head -> next = NULL;
        head -> data = ele;
        return head;
    }
    node* insert = malloc(sizeof(*insert));
    insert -> data = ele;
    insert -> next = head;
    return insert;
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
    node* head = NULL;
    while (1) {
        int ele;
        switch(ch) {
            case 1:
                printf("Enter element to insert: ");
                scanf("%d", &ele);
                head = insert_start(head, ele);
                break;
            case 2:
                traverse(head); break;
            case 3: return 0;
            default: printf("Invalid choice\n");
        }
        printf("Enter choice: ");
        scanf("%d", &ch);
    }
}
