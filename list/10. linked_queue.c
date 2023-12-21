#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct QueueNode {
    element data;
    struct QueueNode *link;
} QueueNode;

typedef struct {
    QueueNode *front;
    QueueNode *rear;
} LinkedQueueType;

int is_empty(LinkedQueueType *q)
{
    return (q->front == NULL);
}

void init(LinkedQueueType *q)
{
    q->front = 0;
    q->rear = 0;
}

void enqueue(LinkedQueueType *q, element data)
{
    QueueNode *temp = (QueueNode *)malloc(sizeof(QueueNode));
    temp->data = data;
    temp->link = NULL;
    if(is_empty(q)) {
        q->front = temp;
        q->rear = temp;
    }
    else {
        q->rear->link = temp;
        q->rear = temp;
    }
}

element dequeue(LinkedQueueType *q)
{
    QueueNode *temp = q->front;
    element data;
    if (is_empty(q)) {
        fprintf(stderr, "queue is empty\n");
        exit(1);
    }
    else {
        data = temp->data;
        q->front = q->front->link;
        if(q->front == NULL) {
            q->rear= NULL;
        }
        free(temp);
        
        return data;
    }
}

void print_queue(LinkedQueueType *q)
{
    QueueNode *p;
    for (p = q->front; p != NULL; p = p->link) {
        printf("%d->", p->data);
    }
    printf("NULL\n");
}

int main() 
{
    LinkedQueueType queue;
    
    init(&queue);
    
    for (int i = 1; i <= 3; i++) {
        enqueue(&queue, i);
        print_queue(&queue);
    }
    for (int i = 1; i <= 3; i++) {
        dequeue(&queue);
        print_queue(&queue);
    }

    return 0;
}