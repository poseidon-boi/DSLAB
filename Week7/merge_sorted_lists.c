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

/** Traverses the list
 * @param head The head node of the linked list
 */
void traverse(node* head) {
    if (!head) {
        printf("NULL\n");
        return;
    }
    for (node* cur = head; cur; cur = cur -> next)
        printf("%d ", cur -> data);
    printf("\n");
}

/** Inserts ins before ele
 * @param head The head node of the linked list
 * @param ele The existing element
 * @param ins The element to insert
 * @return Returns 0 if successfully inserted, 1 if failed
 */
node* insert_before(node* head, int ele, int ins) {
    if (head -> data == ele) {
        node* insert = malloc(sizeof(*insert));
        insert -> data = ins;
        insert -> next = head;
        head = insert;
        return head;
    }
    node* cur = head;
    for (; cur -> next; cur = cur -> next)
        if (cur -> next -> data == ele)
            break;
    node *insert = malloc(sizeof(*insert));
    insert -> data = ins;
    insert -> next = cur -> next;
    cur -> next = insert;
    return head;
}

/** Inserts an element in sorted order, works as intended
 *  only if list is already sorted in ascending order
 * @param head The head node of the linked list
 * @param ele The element to be inserted
 * @return Returns the updated head node of the linked list
 */
node* insert_sort(node* head, int ele) {
    if (!head) {
        head = malloc(sizeof(*head));
        head -> next = NULL;
        head -> data = ele;
        return head;
    }
    node* insert = malloc(sizeof(*insert));
    insert -> data = ele;
    node* cur = head;
    for (; cur -> next; cur = cur -> next)
        if (cur -> data > ele) {
            head = insert_before(head, cur -> data, ele);
            return head;
        }
    if (cur -> data > ele) {
        head = insert_before(head, cur -> data, ele);
        return head;
    }
    cur -> next = insert;
    insert -> next = NULL;
    return head;
}

/** Merges two linked lists that are sorted in ascending order.
 *  Empties the second list.
 * @param head1 The head node of the first linked list
 * @param head2 The head node of the second linked list
 * @return Returns the head node of the resulting linked list.
 *         Returns NULL if both linked lists are empty.
 */
node* merge(node* head1, node* head2) {
    if (!head1)
        return head2;
    if (!head2)
        return head1;
    node* newhead, * cur1, * cur2;
    if (head1 -> data <= head2 -> data) {
        newhead = head1;
        cur1 = newhead;
        cur2 = head2;
    }
    else {
        newhead = head2;
        cur1 = newhead;
        cur2 = head1;
    }
    while(cur1 && cur2) {
        for (; cur1 -> next && (cur1 -> next -> data <= cur2 -> data); cur1 = cur1 -> next);
        node* temp1 = cur1 -> next, * temp2 = cur2;
        cur1 -> next = cur2;
        cur2 = temp1;
        cur1 = temp2;
    }
    return newhead;
}

int main() {
    printf("1. Insert into list 1\n2. Insert into list 2\n"
           "3. Merge into list 1\n4. Traverse list 1\n"
           "5. Traverse list 2\n6. Exit\nEnter choice: ");
    int ch;
    scanf("%d", &ch);
    node* head1 = NULL, * head2 = NULL;
    while (1) {
        int ele;
        switch(ch) {
            case 1:
                printf("Enter element to insert: ");
                scanf("%d", &ele);
                head1 = insert_sort(head1, ele);
                break;
            case 2:
                printf("Enter element to insert: ");
                scanf("%d", &ele);
                head2 = insert_sort(head2, ele);
                break;
            case 3:
                head1 = merge(head1, head2);
                head2 = NULL;
                break;
            case 4: traverse(head1); break;
            case 5: traverse(head2); break;
            case 6: return 0;
            default: printf("Invalid choice\n");
        }
        printf("Enter choice: ");
        scanf("%d", &ch);
    }
}