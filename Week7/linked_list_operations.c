#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node* next;
} node;

node* head = NULL;

int list_len() {
    if (!head)
        return 0;
    if (!(head -> next))
        return 1;
    int len;
    node* cur = head;
    for (len = 0; cur; len++, cur = cur -> next);
    return len;
}

int insert_before(int ele, int data) {
    if (!head)
        return 1;
    if (head -> data == ele) {
        node* insert = malloc(sizeof(*insert));
        insert -> data = data;
        insert -> next = head;
        head = insert;
        return 0;
    }
    node* cur = head;
    for (; cur -> next; cur = cur -> next)
        if (cur -> next -> data == ele)
            break;
    if (!cur -> next)
        return 1;
    node *insert = malloc(sizeof(*insert));
    insert -> data = data;
    insert -> next = cur -> next;
    cur -> next = insert;
    return 0;
}

int insert_after(int ele, int data) {
    if (!head)
        return 1;
    node* cur = head;
    for (; cur; cur = cur -> next)
        if (cur -> data == ele)
            break;
    if (!cur)
        return 1;
    node *insert = malloc(sizeof(*insert));
    insert -> data = data;
    insert -> next = cur -> next;
    cur -> next = insert;
    return 0;
}

int delete(int ele) {
    if (!head)
        return 1;
    if (head -> data == ele) {
        head = head -> next;
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
    return 0;
}

void traverse() {
    if (!head) {
        printf("NULL\n");
        return;
    }
    for (node* cur = head; cur; cur = cur -> next)
        printf("%d ", cur -> data);
    printf("\n");
}

void reverse() {
    int len = list_len();
    if (len < 2)
        return;
    node* cur = head;
    for (int i = 0; i <= len/2; i++) {
        node* prev = head;
        for (int j = 0; j < len-i-1; j++)
            prev = prev -> next;
        int temp = cur -> data;
        cur -> data = prev -> data;
        prev -> data = temp;
        cur = cur -> next;
    }
}

void sort() {
    int len = list_len();
    if (len < 2)
        return;
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

void delete_alternate() {
    if (!head)
        return;
    for (node* cur = head; cur && cur -> next; cur = cur -> next) {
        node* deleted = cur -> next;
        cur -> next = cur -> next -> next;
        free(deleted);
    }
}

void insert_sort(int ele) {
    if (!head) {
        head = malloc(sizeof(*head));
        head -> next = NULL;
        head -> data = ele;
        return;
    }
    node* insert = malloc(sizeof(*insert));
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
}

int main() {
    printf("1. Insert before element\n2. Insert after element\n3. Delete\n4. Traverse\n");
    printf("5. Reverse\n6. Sort\n7. Delete alternate\n8. Insert in sorted\n9. Exit\nEnter choice: ");
    int ch;
    scanf("%d", &ch);
    while (1) {
        int ele, ins, error = 0;
        switch(ch) {
            case 1:
                printf("Enter existing and insert element: ");
                scanf("%d %d", &ele, &ins);
                error = insert_before(ele, ins);
                break;
            case 2:
                printf("Enter existing and insert element: ");
                scanf("%d %d", &ele, &ins);
                error = insert_after(ele, ins);
                break;
            case 3:
                printf("Enter element to delete: ");
                scanf("%d", &ele);
                error = delete(ele);
                break;
            case 4: traverse(); break;
            case 5: reverse(); break;
            case 6: sort(); break;
            case 7: delete_alternate(); break;
            case 8: printf("Enter element to insert: ");
                scanf("%d", &ins);
                insert_sort(ins);
                break;
            case 9:
                return 0;
            default: printf("Invalid choice\n");
        }
        if (error)
            printf("Operation failed\n");
        printf("Enter choice: ");
        scanf("%d", &ch);
    }
}