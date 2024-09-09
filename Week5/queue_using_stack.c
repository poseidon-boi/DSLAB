#include<stdio.h>
#define MAX 20

int stack1[MAX],stack2[MAX];
int top1=-1;
int top2=-1;

void enqueue(int val){
    if(top1==MAX-1)
        printf("Queue is full");
    else
        stack1[++top1]=val;
}

void dequeue(){
    while(top1!=-1)
        stack2[++top2]=stack1[top1--];
    if(top2==-1)
        printf("Queue is empty\n");
    else
        printf("Returned value is: %d\n",stack2[top2--]);
    while(top2 != -1)
        stack1[++top1] = stack2[top2--];
}

void display() {
    printf("Queue: ");
    for (int i = 0; i <= top1; i++)
        printf("%d ", stack1[i]);
    printf("\n");
}

int main()
{
    int choice;
    int val;
    while (1) {
        printf("1. Enqueue\n");
        printf("2. Dequeue\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:  
                printf("Enter the value to enqueue: ");
                scanf("%d",&val);
                enqueue(val);
                display();
                break;

            case 2:  
                dequeue();
                display();
                break;
            case 3: 
                return 0;
                break;
            default:
                printf("Invalid choice!\n");
        }
    }
}