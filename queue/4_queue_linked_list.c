#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct Queue {
    element value;
    struct Queue *link;
}Queue;

typedef struct QueueType {
    Queue *pHead;
    Queue *pTail;
}QueueType;

void init(QueueType *q);
element isEmpty(QueueType *q);
element isFull(QueueType *q);
void enqueue(QueueType *q, element value);
void printQueue(QueueType *q);
element dequeue(QueueType *q);
element peak(QueueType *q);



int main() 
{
    QueueType qt;
    
    init(&qt);
    
    for (int i = 1; i <= 3; i++)
    {
        enqueue(&qt, i);
    }
    printQueue(&qt);
    
    for (int i = 1; i <= 3; i++)
    {
        dequeue(&qt);

        printQueue(&qt);
    }

    return 0;
}

void init(QueueType *q)
{
    q->pHead = q->pTail = 0;
}

int isEmpty(QueueType *q)
{
    return q->pHead == NULL;
}

int isFull(QueueType *q)
{
    return 0;
}

/*
    큐에 원소를 삽입한다.
    시간복잡도: O(1)
*/
void enqueue(QueueType *q, element value)
{
    Queue *newNode = (Queue *) malloc(sizeof(Queue));
    newNode->value = value;
    newNode->link = NULL;
    
    // 처음 삽입하는 경우
    if (isEmpty(q)) 
    {
        q->pHead = newNode;
        q->pTail = newNode;
        return;
    }
    
    q->pTail->link = newNode;
    q->pTail = newNode;
}

/*
    큐에서 원소를 삭제한다.
    시간복잡도: O(1)
*/
element dequeue(QueueType *q)
{
    Queue *temp = q->pHead;
    element data;

    if (isEmpty(q)) 
    {
        fprintf(stderr, "queue is empty\n");
        exit(1);
    }
    else
    {
        data = temp->value;
        q->pHead = temp->link;

         // 이동 후에 값이 없는 경우
        if (q->pHead == NULL)
        {
            q->pTail = NULL;
        }
        free(temp);

        return data;
    }
}

void printQueue(QueueType *q)
{
    Queue *p;
    for (p = q->pHead; p != NULL; p = p->link)
    {
        printf("%d -> ", p->value);
    }
    printf("NULL\n");
}

/*
    큐 가장 앞에 있는 원소를 반환한다.
*/
element peak(QueueType *q)
{
    if (q->pHead == NULL) 
    {
        fprintf(stderr, "queue is empty\n");
        exit(1);
    }
    return q->pHead->value;
}
