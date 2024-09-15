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

/** Finds the length of the linked list
 * @param head The head node of the linked list
 * @return The length of the linked list
 */
int length(node* head) {
    int len = 0;
    for (node* cur = head; cur; cur = cur -> next, len++);
    return len;
}

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

/** Merges two linked lists and returns a brand new linked list. Alternates elements of the bigger and smaller linked list.
 * @param head1 The head node of the first linked list
 * @param head2 The head node of the second linked list
 * @return Returns the head node of the resulting linked list. Returns NULL if both linked lists are empty.
 */
node* merge(node* head1, node* head2) {
    if (!head1 && !head2)
        return NULL;
    node* bigcur, * smallcur, * newhead, *newcur;
    if (length(head1) >= length(head2)) {
        smallcur = head2;
        newhead = malloc(sizeof(*newhead));
        newhead -> data = head1 -> data;
        newcur = newhead;
        bigcur = head1 -> next;
    }
    else {
        smallcur = head1;
        newhead = malloc(sizeof(*newhead));
        newhead -> data = head2 -> data;
        newcur = newhead;
        bigcur = head2 -> next;
    }
    for (; smallcur; smallcur = smallcur -> next, bigcur = bigcur -> next) {
        node* smalltemp = malloc(sizeof(*smalltemp));
        node* bigtemp = malloc(sizeof(*bigtemp));
        smalltemp -> data = smallcur -> data;
        bigtemp -> data = bigcur -> data;
        newcur -> next = smalltemp;
        smalltemp -> next = bigtemp;
        newcur = newcur -> next -> next;
    }
    for (; bigcur; bigcur = bigcur -> next, newcur = newcur -> next) {
        node* temp = malloc(sizeof(*temp));
        temp -> data = bigcur -> data;
        newcur -> next = temp;
    }
    return newhead;
}

int main() {
    printf("1. Insert into list 1\n2. Insert into list 2\n"
           "3. Merge lists into new list\n4. Traverse list 1\n"
           "5. Traverse list 2\n6. Traverse merged list\n7. Exit\n"
           "Enter choice: ");
    int ch;
    scanf("%d", &ch);
    node* head1 = NULL, * head2 = NULL, * head3 = NULL;
    while (1) {
        int ele;
        switch(ch) {
            case 1:
                printf("Enter element to insert: ");
                scanf("%d", &ele);
                head1 = insert_start(head1, ele);
                break;
            case 2:
                printf("Enter element to insert: ");
                scanf("%d", &ele);
                head2 = insert_start(head2, ele);
                break;
            case 3:
                head3 = merge(head1, head2);
                break;
            case 4: traverse(head1); break;
            case 5: traverse(head2); break;
            case 6: traverse(head3); break;
            case 7: return 0;
            default: printf("Invalid choice\n");
        }
        printf("Enter choice: ");
        scanf("%d", &ch);
    }
}