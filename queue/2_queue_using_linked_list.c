#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct Queue 
{
    element value;
    struct Queue *link;
}Queue;

typedef struct QueueType 
{
    Queue *pHead;
    Queue *pTail;
}QueueType;

void init(QueueType *q);
void enqueue(QueueType *q, element value);
void print(QueueType *q);
element dequeue(QueueType *q);
element peak(QueueType *q);

int main() 
{
    QueueType qt;
    
    init(&qt);
    
    for (int i = 1; i <= 3; i++) {
        enqueue(&qt, i);
    }
    print(&qt);
    
    for (int i = 1; i <= 3; i++) {
        dequeue(&qt);
        printf("dequeue: ");
        print(&qt);
    }

    return 0;
}

void init(QueueType *q)
{
    q->pHead = NULL;
    q->pTail = NULL;
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
    if (q->pHead == NULL) 
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
    if (q->pHead == NULL) 
    {
        fprintf(stderr, "queue is empty\n");
        exit(1);
    }
    
    element delValue = q->pHead->value; // 삭제할 노드의 값
    Queue *temp = q->pHead; // 삭제할 노드를 임시로 저장
    q->pHead = q->pHead->link;
    
    free(temp); // 임시 변수를 사용하여 메모리 해제
    
    // 이동 후에 값이 없는 경우
    if (q->pHead == NULL) 
    {
        q->pTail = NULL;
    }
    return delValue;
}

void print(QueueType *q)
{
    Queue *p = q->pHead;
    if (p == NULL) 
    {
        fprintf(stderr, "queue is empty\n");
        return;
    }
    
    while (p != q->pTail) 
    {
        printf("%d->", p->value);
        p = p->link;
    }
    printf("%d\n", p->value);
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


/*
print result:
    1->2->3
    dequeue: 2->3
    dequeue: 3
    dequeue: queue is empty
*/