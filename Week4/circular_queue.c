#include <stdio.h>
#include <stdlib.h>

#define ERROR_VAL -3684723

void enqueue(int arr[], int size, int front, int *rear, int data) {
    if((*rear+1) % size == front) {
        printf("Queue is full\n");
        return;
    }
    *rear = (*rear + 1) % size;
    arr[*rear] = data;
}

int dequeue(int arr[], int size, int *front, int rear) {
    if(*front == rear) {
        printf("Queue is empty\n");
        return ERROR_VAL;
    }
    *front = (*front + 1) % size;
    int data = arr[*front];
    return data;
}

int main() {
    int n;
    printf("Enter the size: ");
    scanf("%d", &n);
    int arr[n], ch, front = 0, rear = 0, data;
    printf("Enter a choice:\n1. Enqueue\n2. Dequeue\n3. Exit\n");
    scanf("%d", &ch);
    while (1) {
        switch (ch) {
        case 1:
            printf("Enter data: ");
            scanf("%d", &data);
            if (data == ERROR_VAL) {
                printf("Invalid data\n");
                break;
            }
            enqueue(arr, n, front, &rear, data);
            break;
        case 2:
            data = dequeue(arr, n, &front, rear);
            if (data == ERROR_VAL)
                break;
            printf("Dequeued %d\n", data);
            break;
        case 3:
            printf("Thank you!");
            return 0;
        default:
            printf("Invalid choice\n");
        }
        printf("Enter a choice: ");
        scanf("%d", &ch);
    }
}
