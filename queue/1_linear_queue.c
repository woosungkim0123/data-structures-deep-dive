#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 5

typedef int element;
typedef struct {
    element data[MAX_QUEUE_SIZE];
    int front, rear;
} Queue;

void error(char *message);
void initQueue(Queue *q);
int isEmpty(Queue *q);
int isFull(Queue *q);
void enqueue(Queue *q, element item);
element dequeue(Queue *q);
element peek(Queue *q);
void printQueue(Queue *q);

/**
 * 배열을 이용한 큐
*/
int main() 
{
    Queue q;
    initQueue(&q);
    
    enqueue(&q, 1);
    printQueue(&q);
    enqueue(&q, 2);
    printQueue(&q);
    enqueue(&q, 3);
    printQueue(&q);

    int item = 0;
    item = dequeue(&q);
    printQueue(&q);
    item = dequeue(&q);
    printQueue(&q);
    item = dequeue(&q);
    printQueue(&q);


    return 0;
}

void error(char *message) 
{
    fprintf(stderr, "%s\n", message);
    exit(1);
}

void initQueue(Queue *q) 
{
    q->front = q->rear = 0;
}

int isEmpty(Queue *q) 
{
    return (q->front == q->rear);
}

int isFull(Queue *q) 
{
    return q->rear == (MAX_QUEUE_SIZE - 1);
}

void enqueue(Queue *q, element item) 
{
    if (isFull(q)) 
    {
        error("큐 포화 상태");
        return;
    }
    q->rear++;
    q->data[q->rear] = item;
}

element dequeue(Queue *q) 
{
    if (isEmpty(q)) 
    {
        error("큐 공백 상태");
        return -1;
    }
    q->front++;
    return q->data[q->front];
}

element peek(Queue *q) 
{
    if (isEmpty(q)) 
    {
        error("큐 공백 상태");
        return -1;
    }
    return q->data[q->front + 1];
}

void printQueue(Queue *q) 
{
    int i;
    printf("Queue : [");
    for (i = q->front + 1; i <= q->rear; i++) 
    {
        printf("%d ", q->data[i]);
    }
    printf("] ");
}

