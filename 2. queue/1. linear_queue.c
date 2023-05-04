#include <stdio.h>
#include <stdlib.h>
#define MAX_QUEUE_SIZE 5

typedef int element;
typedef struct {
    int front;
    int rear;
    element data[MAX_QUEUE_SIZE];
} Queue;

void error(char* message)
{
    fprintf(stderr, "%s\n", message);
    exit(1);
}

void init_queue(Queue* q)
{
    q->rear = -1;
    q->front = -1;
}

void queue_print(Queue* q)
{
    for (int i = 0; i < MAX_QUEUE_SIZE; i++)
    {
        if (i <= q->front || i > q->rear)
        {
            printf("   | ");
        }
        else
        {
            printf("%d | ", q->data[i]);
        }
    }
    printf("\n");
}

int is_full(Queue* q)
{
    if (q->rear == MAX_QUEUE_SIZE - 1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int is_empty(Queue* q)
{
    if (q->front == q->rear)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void enqueue(Queue* q, int item)
{
    if (is_full(q))
    {
        error("queue is full");
        return;
    }
    q->data[++(q->rear)] = item;
}

int dequeue(Queue* q)
{
    if (is_empty(q))
    {
        error("queue is empty");
        return -1;
    }
    return q->data[++(q->front)];
}

int main() {
    Queue q;

    init_queue(&q);

    enqueue(&q, 10);
    queue_print(&q);
    enqueue(&q, 20);
    queue_print(&q);
    enqueue(&q, 40);
    queue_print(&q);

    dequeue(&q);
    queue_print(&q);
    dequeue(&q);
    queue_print(&q);

    return 0;
}
