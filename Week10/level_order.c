#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

/** Traverses the given binary tree using level order traversal
 * @param root The root of the binary tree
 */
void level_order(node* root);


/** Enqueues an element to the circular queue
 * @param queue The array representing the queue
 * @param size The size of the array
 * @param front The front index of the queue
 * @param rear Pointer to the rear index of the queue
 * @param data The data to enqueue
 * @return 0 if successfully enqueued, 1 if failed(Queue full)
 */
int enqueue(node** queue, int size, int front, int *rear, node* data);

/** Dequeues an element from the circular queue
 * @param queue The array representing the queue
 * @param size The size of the array
 * @param front Pointer to the front index of the queue
 * @param rear The rear index of the queue
 * @return The dequeued element. Returns NULL if empty
 */
node* dequeue(node** queue, int size, int *front, int rear);

int main() {

    printf("1. Insert element into tree \n"
           "2. Print tree\n"
           "3. Traverse in level order\n"
           "4. Exit\n");

    node* tree = NULL;

    while (1) {

        printf("Enter choice: ");
        int ch, ele;
        if (!scanf("%d", &ch)) {
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            ch = -1;
        }

        switch (ch)
        {
        case 1:
            printf("Enter element to insert: ");
            if (!scanf("%d", &ele)) {
                int c;
                while ((c = getchar()) != '\n' && c != EOF);
                printf("Not a number\n");
                break;
            }
            tree = insert(tree, ele);
            break;
        case 2:
            if (!tree)
                printf("NULL\n");
            print_tree(tree, 0);
            break;
        case 3: level_order(tree); break;
        case 4: return EXIT_SUCCESS;
        default: printf("Invalid choice\n");
        }

    }

}

int enqueue(node** queue, int size, int front, int *rear, node* data) {
    if((*rear+1) % size == front) {
        printf("Queue is full\n");
        return 1;
    }
    *rear = (*rear + 1) % size;
    queue[*rear] = data;
    return 0;
}

node* dequeue(node** queue, int size, int *front, int rear) {
    if(*front == rear) {
        printf("Queue is empty\n");
        return NULL;
    }
    *front = (*front + 1) % size;
    node* data = queue[*front];
    return data;
}

void level_order(node* root) {
    if (!root) {
        printf("NULL\n");
        return;
    }
    const int queue_size = 512;
    node** queue = malloc(sizeof(*queue) * queue_size);
    int front = -1, rear = -1;
    int error = enqueue(queue, queue_size, front, &rear, root);
    if (error)
        return;
    while (front != rear) {
        node* temp = dequeue(queue, queue_size, &front, rear);
        if (!temp)
            return;
        printf("%d ", temp -> data);
        if (temp -> left) {
            error = enqueue(queue, queue_size, front, &rear, temp -> left);
            if (error)
                return;
        }
        if (temp -> right) {
            error = enqueue(queue, queue_size, front, &rear, temp -> right);
            if (error)
                return;
        }
    }
    printf("\n");
}