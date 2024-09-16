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

/** Inserts an element in sorted order, works as intended 
 *  only if list is already sorted in ascending order
 * @param list Pointer array containing head and tail of linked list
 * @param ele The element to insert
 */
void insert_sort(node** list, int ele) {
    if (!list[HEAD]) {
        list[HEAD] = malloc(sizeof(**list));
        list[HEAD] -> next = NULL;
        list[HEAD] -> prev = NULL;
        list[HEAD] -> data = ele;
        list[TAIL] = list[HEAD];
        return;
    }
    node* insert = malloc(sizeof(*insert));
    insert -> data = ele;
    node* cur = list[HEAD];
    for (; cur -> next; cur = cur -> next)
        if (cur -> data > ele) {
            insert -> prev = cur -> prev;
            if (!insert -> prev)
                list[HEAD] = insert;
            else
                insert -> prev -> next = insert;
            cur -> prev = insert;
            insert -> next = cur;
            return;
        }
    if (cur -> data > ele) {
        insert -> prev = cur -> prev;
        if (!insert -> prev)
            list[HEAD] = insert;
        else
            insert -> prev -> next = insert;
        cur -> prev = insert;
        insert -> next = cur;
        return;
    }
    cur -> next = insert;
    insert -> prev = cur;
    list[TAIL] = insert;
    insert -> next = NULL;
}

/** Prints the unique elements of a sorted linked list in order
 * @param cur The node to start printing from
 */
static void print_unique(node* cur) {
    while (cur) {
            int temp = cur -> data;
            for (; cur && cur -> data == temp; cur = cur -> next);
            printf("%d ", temp);
        }
    printf("\n");
}

/** Prints the union of two linked lists
 * @param list1 Pointer array containing head and tail of list 1
 * @param list2 Pointer array containing head and tail of list 2
 */
void print_union(node** list1, node** list2) {
    if (!list1[HEAD] && !list2[HEAD]) {
        printf("NULL\n");
        return;
    }
    if (!list1[HEAD]) {
        print_unique(list2[HEAD]);
        return;
    }
    if (!list2[HEAD]) {
        print_unique(list1[HEAD]);
        return;
    }
    node* cur1, * cur2;
    if (list1[HEAD] -> data <= list2[HEAD] -> data) {
        cur1 = list1[HEAD];
        cur2 = list2[HEAD];
    }
    else {
        cur1 = list2[HEAD];
        cur2 = list1[HEAD];
    }
    while (cur1 && cur2) {
        int temp = cur1 -> data;
        for (;cur1 && cur1 -> data == temp; cur1 = cur1 -> next);
        for (;cur2 && cur2 -> data == temp; cur2 = cur2 -> next);
        printf("%d ", temp);
        if (!cur1) {
            print_unique(cur2);
            return;
        }
        if (!cur2) {
            print_unique(cur1);
            return;
        }
        if (cur2 -> data < cur1 -> data) {
            node* tempnode = cur1;
            cur1 = cur2;
            cur2 = tempnode;
        }
    }
    printf("\n");
}

/** Prints the intersection of two linked lists
 * @param list1 Pointer array containing head and tail of list 1
 * @param list2 Pointer array containing head and tail of list 2
 */
void print_intersection(node** list1, node** list2) {
    if (!list1[HEAD] || !list2[HEAD]) {
        printf("NULL\n");
        return;
    }
    node* cur1, * cur2;
    int notnull = 0;
    if (list1[HEAD] -> data <= list2[HEAD] -> data) {
        cur1 = list1[HEAD];
        cur2 = list2[HEAD];
    }
    else {
        cur1 = list2[HEAD];
        cur2 = list1[HEAD];
    }
    while (cur1 && cur2) {
        int temp = cur1 -> data, printtemp = 0;
        for (;cur1 && cur1 -> data == temp; cur1 = cur1 -> next);
        if (cur2 -> data == temp) {
            printtemp = 1;
            notnull = 1;
        }
        for (;cur2 && cur2 -> data == temp; cur2 = cur2 -> next);
        if (printtemp)
            printf("%d ", temp);
        if (!cur1) {
            if (notnull)
                printf("\n");
            else
                printf("NULL\n");
            return;
        }
        if (!cur2) {
            if (notnull)
                printf("\n");
            else
                printf("NULL\n");
            return;
        }
        if (cur2 -> data < cur1 -> data) {
            node* tempnode = cur1;
            cur1 = cur2;
            cur2 = tempnode;
        }
    }
    if (notnull)
        printf("\n");
    else
        printf("NULL\n");
}

int main() {
    printf("1. Insert into list 1\n2. Insert into list 2\n"
           "3. Traverse list 1\n4. Traverse list 2\n"
           "5. Print union\n6. Print intersection\n"
           "7. Exit\nEnter choice: ");
    int ch;
    scanf("%d", &ch);
    node** list1 = malloc(2*sizeof(*list1)), ** list2 = malloc(2*sizeof(*list2));
    list1[0] = list1[1] = list2[0] = list2[1] = NULL;
    while (1) {
        int ele;
        switch(ch) {
            case 1:
                printf("Enter element to insert: ");
                scanf("%d", &ele);
                insert_sort(list1, ele);
                break;
            case 2:
                printf("Enter element to insert: ");
                scanf("%d", &ele);
                insert_sort(list2, ele);
                break;
            case 3: traverse(list1[0]); break;
            case 4: traverse(list2[0]); break;
            case 5: print_union(list1, list2); break;
            case 6: print_intersection(list1, list2); break;
            case 7: return 0;
            default: printf("Invalid choice\n");
        }
        printf("Enter choice: ");
        scanf("%d", &ch);
    }
}