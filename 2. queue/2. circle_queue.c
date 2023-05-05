#include <stdio.h>
#include <stdlib.h>
#define MAX_QUEUE_SIZE 5

typedef int element;
typedef struct {
    element data[MAX_QUEUE_SIZE];
    int front;
    int rear;
} Queue;

void error(char* message)
{
    fprintf(stderr, "%s\n", message);
    exit(1);
}

void init_queue(Queue* q)
{
    q->rear = 0;
    q->front = 0;
}

int is_full(Queue* q)
{
    return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}

int is_empty(Queue* q)
{
    return (q->front == q->rear);
}

void queue_print(Queue* q)
{
    printf("QUEUE(front=%d rear=%d) = ", q->front, q->rear);
    if (!is_empty(q))
    {
        int i = q->front;
        do
        {
            i = (i + 1) % MAX_QUEUE_SIZE;
            printf("%d | ", q->data[i]);
            if (i == q->rear)
            {
                break;
            }
        } while (i != q->front);
    }
    printf("\n");
}

void enqueue(Queue* q, int item)
{
    if (is_full(q))
    {
        error("queue is full");
    }
    q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
    q->data[q->rear] = item;
}

element dequeue(Queue* q)
{
    if (is_empty(q))
    {
        error("queue is empty");
    }
    q->front = (q->front + 1) % MAX_QUEUE_SIZE;
    return q->data[q->front];
}

element peek(Queue* q)
{
    if (is_empty(q))
    {
        error("queue is empty");
    }
    return q->data[(q->front + 1) % MAX_QUEUE_SIZE];
}

int main() {
    Queue queue;
    int element;

    init_queue(&queue);

    while (!is_full(&queue))
    {
        printf("write Integer: ");
        scanf("%d", &element);
        enqueue(&queue, element);
        queue_print(&queue);
    }
    printf("=== queue is full ===\n");

    while (!is_empty(&queue))
    {
        element = dequeue(&queue);
        printf("out number = %d\n", element);
        queue_print(&queue);
    }
    printf("=== queue is empty ===\n");

    return 0;
}