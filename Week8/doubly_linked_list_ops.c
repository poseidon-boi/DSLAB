#include <stdio.h>
#include <stdlib.h>

/** Node of the doubly linked list
 * @param data
 * @param next
 * @param prev
 */
typedef struct node {
    /** The data stored in the node */
    int data;
    /** The pointer to the previous node */
    struct node* prev;
    /** The pointer to the next node */
    struct node* next;
} node;

/** The head node */
static node* head;
/** The tail node */
static node* tail;
/** The length of the linked list */
static int len;

/** Inserts an element at the tail end of the list
 * @param ele The element to insert
 */
void insert_tail(int ele) {
    node* insert = malloc(sizeof(*insert));
    insert -> data = ele;
    insert -> next = NULL;
    if(!head) {
        insert -> prev = NULL;
        head = tail = insert;
        len = 1;
        return;
    }
    tail -> next = insert;
    insert -> prev = tail;
    tail = insert;
    len++;
}

/** Deletes an element from the tail end of the linked list */
int delete_tail() {
    if (!head)
        return 1;
    if (!tail -> prev) {
        free(tail);
        head = tail = NULL;
        len = 0;
        return 0;
    }
    tail = tail -> prev;
    free(tail -> next);
    tail -> next = NULL;
    len--;
    return 0;
}

/** Inserts an element at the given position of the linked list
 * @param ele The element to insert
 * @param pos The position to insert into (1 inserts at beginning, length+1 at end)
 * @return Returns 1 if error(invalid position), 0 if successful
 */
int insert_pos(int ele, int pos) {
    if (pos > len + 1 || pos < 1)
        return 1;
    if (pos == len + 1) {
        insert_tail(ele);
        len++;
        return 0;
    }
    node* cur = head;
    for (int i = 1; i < pos; i++, cur = cur -> next);
    node* insert = malloc(sizeof(*insert));
    insert -> data = ele;
    if (pos == 1)
        head = insert;
    insert -> next = cur;
    insert -> prev = cur -> prev;
    if (cur -> prev)
        cur -> prev -> next = insert;
    cur -> prev = insert;
    len++;
    return 0;
}

/** Deletes an element from the given position in the linked list
 * @param pos The position of the element to delete
 * @return Returns 1 if error(invalid position), 0 if successful
 */
int delete_pos(int pos) {
    if (pos > len || pos < 1)
        return 1;
    node* cur = head;
    for (int i = 1; i < pos; i++, cur = cur -> next);
    if (cur -> prev)
        cur -> prev -> next = cur -> next;
    if (cur -> next)
        cur -> next -> prev = cur -> next;
    if (pos == 1)
        head = head -> next;
    if (pos == len)
        tail = tail -> prev;
    free(cur);
    len--;
    return 0;
}

/** Inserts ins after ele
 * @param ele The existing element
 * @param ins The element to insert
 * @return Returns 0 if successfully inserted, 1 if failed
 */
int insert_after(int ele, int ins) {
    if (!head)
        return 1;
    node* cur = head;
    for (; cur; cur = cur -> next)
        if (cur -> data == ele)
            break;
    if (!cur)
        return 1;
    node *insert = malloc(sizeof(*insert));
    insert -> data = ins;
    insert -> next = cur -> next;
    if (insert -> next)
        insert -> next -> prev = insert;
    cur -> next = insert;
    insert -> prev = cur;
    if (cur == tail)
        tail = tail -> next;
    len++;
    return 0;
}

/** Inserts ins before ele
 * @param ele The existing element
 * @param ins The element to insert
 * @return Returns 0 if successfully inserted, 1 if failed
 */
int insert_before(int ele, int ins) {
    if (!tail)
        return 1;
    node* cur = tail;
    for (; cur; cur = cur -> prev)
        if (cur -> data == ele)
            break;
    if (!cur)
        return 1;
    node *insert = malloc(sizeof(*insert));
    insert -> data = ins;
    insert -> prev = cur -> prev;
    if (insert -> prev)
        insert -> prev -> next = insert;
    cur -> prev = insert;
    insert -> next = cur;
    if (cur == head)
        head = head -> prev;
    len++;
    return 0;
}

/** Transverses through the linked list and prints elements, prints NULL if empty */
void traverse() {
    if (!head) {
        printf("NULL\n");
        return;
    }
    for (node* cur = head; cur; cur = cur -> next)
        printf("%d ", cur -> data);
    printf("\n");
}

/** Reverses the list */
void reverse() {
    node* front = head, * back = tail;
    for (int i = 0; i < len/2; i++, front = front -> next, back = back -> prev) {
        int temp = front -> data;
        front -> data = back -> data;
        back -> data = temp;
    }
}

int main() {
    printf("1. Insert at tail\n2. Delete from tail\n"
           "3. Insert at given position\n4. Delete from given position\n"
           "5. Insert after given element\n6. Insert before given element\n"
           "7. Traverse\n8. Reverse\n9. Exit\nEnter choice: ");
    int ch;
    scanf("%d", &ch);
    while (1) {
        int ele, ins, error = 0, pos;
        switch(ch) {
            case 1:
                printf("Enter element to insert: ");
                scanf("%d", &ins);
                insert_tail(ins);
                break;
            case 2: error = delete_tail(); break;
            case 3:
                printf("Enter position and element to insert: ");
                scanf("%d %d", &pos, &ele);
                error = insert_pos(ele, pos);
                break;
            case 4:
                printf("Enter position to delete from: ");
                scanf("%d", &pos);
                error = delete_pos(pos);
                break;
            case 5:
                printf("Enter existing and insert element: ");
                scanf("%d %d", &ele, &ins);
                error = insert_after(ele, ins);
                break;
            case 6:
                printf("Enter existing and insert element: ");
                scanf("%d %d", &ele, &ins);
                error = insert_before(ele, ins);
                break;
            case 7: traverse(); break;
            case 8: reverse(); break;
            case 9: return 0;
            default: printf("Invalid choice\n");
        }
        if (error)
            printf("Operation failed\n");
        printf("Enter choice: ");
        scanf("%d", &ch);
    }
}