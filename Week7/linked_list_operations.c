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

/** The head node */
static node* head;
/** The length of the linked list */
static int len;

/** Inserts ins before ele
 * @param ele The existing element
 * @param ins The element to insert
 * @return Returns 0 if successfully inserted, 1 if failed
 */
int insert_before(int ele, int ins) {
    if (!head)
        return 1;
    if (head -> data == ele) {
        node* insert = (node*) malloc(sizeof(*insert));
        insert -> data = ins;
        insert -> next = head;
        head = insert;
        len++;
        return 0;
    }
    node* cur = head;
    for (; cur -> next; cur = cur -> next)
        if (cur -> next -> data == ele)
            break;
    if (!cur -> next)
        return 1;
    node* insert = (node*) malloc(sizeof(*insert));
    insert -> data = ins;
    insert -> next = cur -> next;
    cur -> next = insert;
    len++;
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
    node* insert = (node*) malloc(sizeof(*insert));
    insert -> data = ins;
    insert -> next = cur -> next;
    cur -> next = insert;
    len++;
    return 0;
}

/** Deletes ele from the linked list, if it exists
 * @return Returns 0 if successfully deleted, 1 if failed
 */
int delete(int ele) {
    if (!head)
        return 1;
    if (head -> data == ele) {
        node* deleted = head;
        head = head -> next;
        free(deleted);
        return 0;
    }
    node* cur = head;
    for (; cur -> next; cur = cur -> next)
        if (cur -> next -> data == ele || !cur)
            break;
    if (!cur -> next)
        return 1;
    node* deleted = cur -> next;
    cur -> next = cur -> next -> next;
    free(deleted);
    len--;
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
    node* cur = head;
    for (int i = 0; i < len/2; i++, cur = cur -> next) {
        node* prev = head;
        for (int j = 0; j < len-i-1; j++)
            prev = prev -> next;
        int temp = cur -> data;
        cur -> data = prev -> data;
        prev -> data = temp;
    }
}

/** Sorts the list in ascending order */
void sort() {
    for (int i = 0; i < len-1; i++) {
        node* cur = head;
        for (int j = 0; j < len - i - 1; j++, cur = cur -> next) {
            if (cur -> data <= cur -> next -> data)
                continue;
            int temp = cur -> data;
            cur -> data = cur -> next -> data;
            cur -> next -> data = temp;
        }
    }
}

/** Deletes alternate nodes in the list */
void delete_alternate() {
    for (node* cur = head; cur && cur -> next; cur = cur -> next) {
        node* deleted = cur -> next;
        cur -> next = cur -> next -> next;
        free(deleted);
        len--;
    }
}

/** Inserts an element in sorted order,
 *  works as intended only if list is already sorted in ascending order
 * @param ele The element to insert
 */
void insert_sort(int ele) {
    if (!head) {
        head = (node*) malloc(sizeof(*head));
        head -> next = NULL;
        head -> data = ele;
        len++;
        return;
    }
    node* insert = (node*) malloc(sizeof(*insert));
    insert -> data = ele;
    node* cur = head;
    for (; cur -> next; cur = cur -> next)
        if (cur -> data > ele) {
            insert_before(cur -> data, ele);
            return;
        }
    if (cur -> data > ele) {
        insert_before(cur -> data, ele);
        return;
    }
    cur -> next = insert;
    insert -> next = NULL;
    len++;
}

int main() {
    printf("1. Insert before element\n2. Insert after element\n"
           "3. Delete\n4. Traverse\n5. Reverse\n6. Sort\n"
           "7. Delete alternate\n8. Insert in sorted\n"
           "9. Exit\nEnter choice: ");
    char ch;
    scanf(" %c", &ch);
    while (1) {
        int ele, ins, error = 0;
        switch(ch) {
            case '1':
                printf("Enter existing and insert element: ");
                if (!scanf("%d", &ele) || !scanf("%d", &ins)) {
                    while (getchar() != '\n');
                    error = 1;
                    break;
                }
                error = insert_before(ele, ins);
                break;
            case '2':
                printf("Enter existing and insert element: ");
                if (!scanf("%d", &ele) || !scanf("%d", &ins)) {
                    while (getchar() != '\n');
                    error = 1;
                    break;
                }
                error = insert_after(ele, ins);
                break;
            case '3':
                printf("Enter element to delete: ");
                if (!scanf("%d", &ele)) {
                    while (getchar() != '\n');
                    error = 1;
                    break;
                }
                error = delete(ele);
                break;
            case '4': traverse(); break;
            case '5': reverse(); break;
            case '6': sort(); break;
            case '7': delete_alternate(); break;
            case '8':
                printf("Enter element to insert: ");
                if (!scanf("%d", &ins)) {
                    while (getchar() != '\n');
                    error = 1;
                    break;
                }
                insert_sort(ins);
                break;
            case '9': return 0;
            default: printf("Invalid choice\n");
        }
        if (error)
            printf("Operation failed\n");
        printf("Enter choice: ");
        scanf(" %c", &ch);
    }
}