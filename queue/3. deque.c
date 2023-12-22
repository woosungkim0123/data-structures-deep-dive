#include <stdio.h>
#include <stdlib.h>
#define MAX_QUEUE_SIZE 5

typedef int element;
typedef struct {
    element data[MAX_QUEUE_SIZE];
    int front;
    int rear;
} Deque;

void error(char* message)
{
    fprintf(stderr, "%s\n", message);
    exit(1);
}

void init_deque(Deque* q)
{
    q->rear = 0;
    q->front = 0;
}

int is_full(Deque* q)
{
    return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}

int is_empty(Deque* q)
{
    return (q->front == q->rear);
}

void deque_print(Deque* q)
{
    printf("Deque(front=%d rear=%d) = ", q->front, q->rear);
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

void add_rear(Deque* q, element item)
{
    if (is_full(q))
    {
        error("queue is full");
    }
    q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
    q->data[q->rear] = item;
}

void add_front(Deque* q, element item)
{
    if (is_full(q))
    {
        error("queue is full");
    }
    q->data[q->front] = item;
    q->front = (q->front - 1 + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;
}

element delete_rear(Deque* q)
{
    int prev = q->rear;
    if (is_empty(q))
    {
        error("queue is empty");
    }
    q->rear = (q->rear - 1 + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;
    return q->data[prev];
}

element delete_front(Deque* q)
{
    if (is_empty(q))
    {
        error("queue is empty");
    }
    q->front = (q->front + 1) % MAX_QUEUE_SIZE;
    return q->data[q->front];
}

element get_rear(Deque* q)
{
    if (is_empty(q))
    {
        error("queue is empty");
    }
    return q->data[q->rear];
}

element get_front(Deque* q)
{
    if (is_empty(q))
    {
        error("queue is empty");
    }
    return q->data[(q->front + 1) % MAX_QUEUE_SIZE];
}

int main() {
    Deque queue;

    init_deque(&queue);

    for (int i = 0; i < 3; i++)
    {
        add_front(&queue, i);
        deque_print(&queue);
    }

    for (int i = 0; i < 3; i++)
    {
        delete_rear(&queue);
        deque_print(&queue);
    }

    return 0;
}