#include <stdio.h>
#include <stdlib.h>
#define HEAD 0
#define TAIL 1

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

/** Inserts an element at the tail end of the list
 * @param list Pointer array containing head and tail of linked list
 * @param ele The element to insert
 */
void insert_tail(node** list, int ele) {
    node* insert = malloc(sizeof(*insert));
    insert -> data = ele;
    insert -> next = NULL;
    if(!list[HEAD]) {
        insert -> prev = NULL;
        list[HEAD] = list[TAIL] = insert;
        return;
    }
    list[TAIL] -> next = insert;
    insert -> prev = list[1];
    list[TAIL] = insert;
}

/** Concatenates list2 to list1
 * @param list1 Pointer array containing head and tail of list 1
 * @param list2 Pointer array containing head and tail of list 2
 */
void concatenate(node** list1, node** list2) {
    if (!list2[HEAD])
        return;
    if (!list1[HEAD]) {
        list1[HEAD] = list2[HEAD];
        list1[TAIL] = list2[TAIL];
        list2[HEAD] = list2[TAIL] = NULL;
        return;
    }
    list1[TAIL] -> next = list2[HEAD];
    list2[HEAD] -> prev = list1[TAIL];
    list1[TAIL] = list2[TAIL];
    list2[HEAD] = list2[TAIL] = NULL;
}

int main() {
    printf("1. Insert into list 1\n2. Insert into list 2\n"
           "3. Concat into list 1\n4. Traverse list 1\n"
           "5. Traverse list 2\n6. Exit\nEnter choice: ");
    char ch;
    scanf(" %c", &ch);
    node** list1 = malloc(2*sizeof(*list1)), ** list2 = malloc(2*sizeof(*list2));
    list1[HEAD] = list1[TAIL] = list2[HEAD] = list2[TAIL] = NULL;
    while (1) {
        int ele, error = 0;
        switch(ch) {
            case '1':
                printf("Enter element to insert: ");
                if (!scanf("%d", &ele)) {
                    while (getchar() != '\n');
                    error = 1;
                    break;
                }
                insert_tail(list1, ele);
                break;
            case '2':
                printf("Enter element to insert: ");
                if (!scanf("%d", &ele)) {
                    while (getchar() != '\n');
                    error = 1;
                    break;
                }
                insert_tail(list2, ele);
                break;
            case '3':
                concatenate(list1, list2);
                break;
            case '4': traverse(list1[HEAD]); break;
            case '5': traverse(list2[HEAD]); break;
            case '6': return 0;
            default: printf("Invalid choice\n");
        }
        if (error)
            printf("Not a number\n");
        printf("Enter choice: ");
        scanf(" %c", &ch);
    }
}