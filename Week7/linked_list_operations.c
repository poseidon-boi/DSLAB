#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    node* next;
} node;

node* head = NULL;

int insert_before(int ele, int data) {
    if (head == NULL)
        return 1;
    if (head -> data == ele) {
        node* insert;
        insert -> data = data;
        insert -> next = head;
        head = insert;
        return 0;
    }
    node* cur = head;
    while (cur -> next -> data != ele && cur != NULL)
        cur = cur -> next;
    if (cur == NULL)
        return 1;
    node *insert;
    insert -> data = data;
    insert -> next = cur -> next;
    cur -> next = insert;
    return 0;
}

int insert_after(int ele, int data) {
    if (head == NULL)
        return 1;
    node* cur = head;
    while (cur -> data != ele && cur != NULL)
        cur = cur -> next;
    if (cur == NULL)
        return 1;
    node *insert;
    insert -> data = data;
    insert -> next = cur -> next;
    cur -> next = insert;
    return 0;
}

int delete(int ele) {
    if (head == NULL)
        return 1;
    if (head -> data == ele) {
        head = head -> next;
        return 0;
    }
    node* cur = head;
    while (cur -> next -> data != ele && cur != NULL)
        cur = cur -> next;
    if (cur == NULL)
        return 1;
    cur -> next = cur -> next -> next;
    return 0;
}

void traverse() {
    if (head == NULL) {
        printf("NULL\n");
        return;
    }
    node* cur = head;
    while (cur -> next != NULL) {
        printf("%d ", cur -> data);
        cur = cur -> next;
    }
}

void reverse() {

}