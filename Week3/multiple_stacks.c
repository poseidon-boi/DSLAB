#include <stdio.h>
#include <stdlib.h>
#define ERROR -9998

void push(int s[], int top[], int size, int num, int data) {
    if (top[num]+1 == (num+1)*size) {
        printf("Stack overflow\n");
        return;
    }
    s[++top[num]] = data;
}

int pop(int s[], int top[], int size, int num) {
    if (top[num] == num*size - 1) {
        printf("Stack underflow\n");
        return ERROR;
    }
    int data = s[top[num]--];
    s[top[num]+1] = 0;
    return data;
}

void display(int arr[], int arr_size) {
    for (int i=0; i<arr_size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int main() {
    printf("Enter number of stacks and size: ");
    int size, n;
    scanf("%d %d", &n, &size);
    int stk[n*size], top[n];
    for(int i=0; i<n; i++)
        top[i] = i*size - 1;
    for (int i=0; i<n*size; i++)
        stk[i] = 0;
    printf("Enter choice:\n1.Push\n2.Pop\n3.Exit\n");
    while (1) {
        int ch, num, data;
        scanf("%d", &ch);
        switch(ch) {
        case 1:
            printf("Enter stack number: ");
            scanf("%d", &num);
            printf("Enter data: ");
            scanf("%d", &data);
            if (data == ERROR) {
                printf("Invalid data\n");
                break;
            }
            push(stk, top, size, num-1, data);
            display(stk, n*size);
            break;
        case 2:
            printf("Enter stack number: ");
            scanf("%d", &num);
            data = pop(stk, top, size, num-1);
            if (data == ERROR)
                break;
            printf("Popped %d\n", data);
            display(stk, n*size);
            break;
        case 3:
            return 0;
        default:
            printf("Invalid choice\n");
        }
        printf("Enter choice: ");
    }
}