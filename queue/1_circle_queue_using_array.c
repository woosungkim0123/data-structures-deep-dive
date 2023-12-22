#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct Queue 
{
    element *arr; // 동적 메모리 주소를 저장하는 포인터
    int front; // 삭제 위치
    int rear; // 삽입 위치
    int count; // 원소 개수
    int capacity; // 배열의 최대 용량
}Queue;

/*
    배열로 큐를 구현할 때 값을 뺀다면 남아 있는 모든 원소를 앞으로 이동해야함
    시간복잡도가 0(N)이 걸림, 이를 보완하기 위해 원형 큐를 사용
*/
void init(Queue *pQueue, int size);
void enqueue(Queue *pQueue, element item);
element dequeue(Queue *pQueue);
void print(const Queue *queue); // 구조체 변수를 수정할 수 없도록
element peek(Queue* q);

int main()
{
    Queue queue;
    init(&queue, 5);

    for (int i = 1; i <= 5; i++)
    {
        enqueue(&queue, i);
    }
    print(&queue);

    dequeue(&queue);
    dequeue(&queue);
    print(&queue);
    
    element value = peek(&queue);
    printf("peeked value: %d\n", value);
    
}

void init(Queue *pQueue, int size)
{
    pQueue->arr = (element *) malloc(sizeof(element) * size);
    pQueue->front = 0;
    pQueue->rear = 0;
    pQueue->count = 0;
    pQueue->capacity = size;
}

/*
    원형 큐에서 원소를 삽입한다.
    시간복잡도: O(1)
*/
void enqueue(Queue *pQueue, element value)
{
    if (pQueue->count == pQueue->capacity)
    {
        printf("Queue oveflow \n");
        return;
    }
    pQueue->arr[pQueue->rear] = value;
    pQueue->rear++;
    pQueue->count++;

    // 범위를 벗어난 인덱스
    if (pQueue->rear == pQueue->capacity)
    {
        pQueue->rear = 0;
    }
}

/*
    원형 큐에서 원소를 꺼낸다.
    시간복잡도: O(1)
*/
element dequeue(Queue *pQueue)
{
    // c++에서는 예외처리, exit 시켜버려도 됨
    if (pQueue->count == 0)
    {
        printf("Queue underflow \n"); 
        return -999999999; // 왠만하면 겹치지 않는 값으로 설정해서 underflow를 체크
    }
    element deletedValue = pQueue->arr[pQueue->front];

    pQueue->front++;
    pQueue->count--;

    if (pQueue->front == pQueue->capacity)
    {
        pQueue->front = 0;
    }
    
    return deletedValue;
}

void print(const Queue *pQueue)
{
    if (pQueue->count == 0)
    {
        printf("Queue is empty \n");
        return;
    }

    for (int i = pQueue->front; i < pQueue->front + pQueue->count; i++)
    {
        printf("%d ", pQueue->arr[i % pQueue->capacity]); // 나머지
    }
    printf("\n");
}

element peek(Queue* q)
{
    return q->arr[(q->front)];
}

/*
print result:
    1 2 3 4 5 
    3 4 5
    peeked value: 3
*/