#include <stdio.h>
#include <stdlib.h>

/** A node of the doubly linked circular list */
typedef struct node {
    /** The data stored in the node */
    int data;
    /** Pointer to the next node */
    struct node* next;
    /** Pointer to the previous node */
    struct node* prev;
} node;

/** The head node of the doubly linked circular list */
node* head = NULL;

/** Inserts an element into the doubly linked circular list
 * @param ele The element to insert
 * @return The updated head node of the list
 */
void insert_ele(int ele) {
    node* temp = malloc(sizeof(*temp));
    temp -> data = ele;
    if (!head) {
        head = temp;
        head -> next = head -> prev = head;
        return;
    }
    temp -> next = head;
    temp -> prev = head -> prev;
    head -> prev -> next = temp;
    head -> prev = temp;
}

/** Deletes the entered element from the doubly linked circular list
 * @param ele The element to delete
 * @return 1 if element does not exist, 0 if successfully deleted
 */
int delete_ele(int ele) {
    if (!head)
        return 1;
    if (head -> data == ele) {
        if (head -> next == head) {
            free(head);
            head = NULL;
            return 0;
        }
        head -> next -> prev = head -> prev;
        head -> prev -> next = head -> next;
        node* temp = head;
        head = head -> next;
        free(temp);
        return 0;
    }
    node* cur = head -> next;
    for (; cur != head && cur -> data != ele; cur = cur -> next);
    if (cur -> data == ele) {
        cur -> prev -> next = cur -> next;
        cur -> next -> prev = cur -> prev;
        free(cur);
        return 0;
    }
    return 1;
}

/** Traverses the doubly linked circular list */
void traverse() {
    if (!head) {
        printf("NULL\n");
        return;
    }
    for (node* cur = head; ; cur = cur -> next) {
        printf("%d ", cur -> data);
        if (cur -> next == head)
            break;
    }
    printf("\n");
}

int main() {
    printf("1. Insert at tail\n2. Delete entered element\n"
           "3. Traverse\n4. Exit\nEnter choice: ");
    int ch;
    scanf("%d", &ch);
    while (1) {
        int ele, error = 0;
        switch(ch) {
            case 1:
                printf("Enter element to insert: ");
                scanf("%d", &ele);
                insert_ele(ele);
                break;
            case 2:
                printf("Enter element to delete: ");
                scanf("%d", &ele);
                error = delete_ele(ele);
                break;
            case 3: traverse(); break;
            case 4: return 0;
            default: printf("Invalid choice\n");
        }
        if (error)
            printf("Element not found in list\n");
        printf("Enter choice: ");
        scanf("%d", &ch);
    }
}