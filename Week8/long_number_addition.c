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
    insert -> prev = list[TAIL];
    list[TAIL] = insert;
}

/** Inserts an element at the head of the list
 * @param list Pointer array containing head and tail of linked list
 * @param ele The element to insert
 */
void insert_head(node** list, int ele) {
    node* insert = malloc(sizeof(*insert));
    insert -> data = ele;
    insert -> next = NULL;
    if(!list[HEAD]) {
        insert -> prev = NULL;
        list[HEAD] = list[TAIL] = insert;
        return;
    }
    list[HEAD] -> prev = insert;
    insert -> next = list[HEAD];
    list[HEAD] = insert;
}

/** Traverses the list
 * @param head The head node of the linked list
 */
void traverse(node* head) {
    if (!head) {
        printf("NULL\n");
        return;
    }
    for (node* cur = head; cur; cur = cur -> next)
        printf("%d", cur -> data);
    printf("\n");
}

node** add(node** num1, node** num2) {
    node** sum = malloc(2*sizeof(*sum));
    node* cur1 = num1[TAIL], * cur2 = num2[TAIL];
    int carry = 0;
    while (cur1 && cur2) {
        int digit = (cur1 -> data + cur2 -> data + carry);
        carry = digit / 10;
        digit %= 10;
        insert_head(sum, digit);
        cur1 = cur1 -> prev;
        cur2 = cur2 -> prev;
    }
    if (!cur1 && !cur2) {
        if (carry)
            insert_head(sum, 1);
        return sum;
    }
    if (!cur1)
        cur1 = cur2;
    insert_head(sum, cur1 -> data + carry);
    cur1 = cur1 -> prev;
    while (cur1) {
        insert_head(sum, cur1 -> data);
        cur1 = cur1 -> prev;
    }
    return sum;
}

int main() {
    printf("Enter the numbers: ");
    node** num1 = malloc(2*sizeof(*num1)), ** num2 = malloc(2*sizeof(*num2));
    char ch;
    int i;
    while ((ch = getchar()) != ' ' && ch != '\n') {
        if (ch < '0' || ch > '9') {
            printf("Invalid number");
            return 1;
        }
        insert_tail(num1, ch-'0');
    }
    while ((ch = getchar()) != ' ' && ch != '\n') {
        if (ch < '0' || ch > '9') {
            printf("Invalid number");
            return 1;
        }
        insert_tail(num2, ch-'0');
    }
    node** sum;
    sum = add(num1, num2);
    printf("The sum is ");
    traverse(sum[HEAD]);
    return 0;
}