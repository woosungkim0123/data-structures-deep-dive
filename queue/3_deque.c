#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 5

typedef int element;
typedef struct Deque {
    element data[MAX_QUEUE_SIZE];
    int front, rear;
}Deque;

void error(char *message);
void initDeque(Deque *q);
int isEmpty(Deque *q);
int isFull(Deque *q);
void addFront(Deque *q, element item);
void addRear(Deque *q, element item);
element deleteFront(Deque *q);
element deleteRear(Deque *q);
element getFront(Deque *q);
element getRear(Deque *q);
void printDeque(Deque *q);

int main() 
{
    Deque q;
    initDeque(&q);
    
    addFront(&q, 1);
    printDeque(&q);
    addFront(&q, 2);
    printDeque(&q);
    addRear(&q, 3);
    printDeque(&q);
    addRear(&q, 4);
    printDeque(&q);
    
    deleteFront(&q);
    printDeque(&q);
    deleteRear(&q);
    printDeque(&q);
    
    return 0;
}

void error(char *message) 
{
    fprintf(stderr, "%s\n", message);
    exit(1);
}

void initDeque(Deque *q) 
{
    q->front = q->rear = 0;
}

int isEmpty(Deque *q) 
{
    return q->front == q->rear;
}

int isFull(Deque *q) 
{
    return (q->rear + 1) % MAX_QUEUE_SIZE == q->front;
}

void addFront(Deque *q, element item) 
{
    if (isFull(q)) 
    {
        error("큐 포화 상태");
        return;
    }
    q->data[q->front] = item;
    q->front = (q->front - 1 + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;
}

void addRear(Deque *q, element item) 
{
    if (isFull(q)) 
    {
        error("큐 포화 상태");
        return;
    }
    q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
    q->data[q->rear] = item;
}

element deleteFront(Deque *q) 
{
    if (isEmpty(q)) 
    {
        error("큐 공백 상태");
        return -1;
    }
    q->front = (q->front + 1) % MAX_QUEUE_SIZE;
    return q->data[q->front];
}

element deleteRear(Deque *q) 
{
    if (isEmpty(q)) 
    {
        error("큐 공백 상태");
        return -1;
    }
    element item = q->data[q->rear];
    q->rear = (q->rear - 1 + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE;
    return item;
}

element getFront(Deque *q) 
{
    if (isEmpty(q)) 
    {
        error("큐 공백 상태");
        return -1;
    }
    return q->data[(q->front + 1) % MAX_QUEUE_SIZE];
}

element getRear(Deque *q) 
{
    if (isEmpty(q)) 
    {
        error("큐 공백 상태");
        return -1;
    }
    return q->data[q->rear];
}

void printDeque(Deque *q) 
{
    printf("Deque: [");
    int i = (q->front + 1) % MAX_QUEUE_SIZE;
    while (i != q->rear) 
    {
        printf("%d ", q->data[i]);
        i = (i + 1) % MAX_QUEUE_SIZE;
    }
    if (!isEmpty(q)) 
    {
        printf("%d", q->data[i]);
    }
    printf("]\n");
}

