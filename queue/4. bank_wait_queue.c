#include <stdio.h>
#include <stdlib.h>
#define MAX_QUEUE_SIZE 100

typedef struct {
    int id;
    int arrival_time;
    int service_time;
} element;
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

void enqueue(Queue* q, element item)
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

int main() 
{
    int minutes = 60;
    int total_wait = 0;
    int total_customers = 0;
    int service_time = 0;
    int service_customer = 0;
    
    Queue queue;
    
    init_queue(&queue);
    
    for(int clock = 0; clock < minutes; clock++)
    {
        printf("현재시작 = %d\n", clock);
        if(rand()%10 < 3)
        {
            element customer;
            customer.id = total_customers++;
            customer.arrival_time = clock;
            customer.service_time = rand() % 3 + 1;
            enqueue(&queue, customer);
            printf("고객 %d이 %d분에 들어옵니다. 업무 처리시간 %d분\n", customer.id, customer.arrival_time, customer.service_time);
        }
        if(service_time > 0)
        {
            printf("==고객 %d 업무처리중입니다.== \n", service_customer);
            service_time--;
        }
        else
        {   
            if(!is_empty(&queue))
            {
                element customer = dequeue(&queue);
                service_customer = customer.id;
                service_time = customer.service_time;
                printf("고객 %d이 %d분에 업무를 시작합니다. 대기시간은 %d분입니다.\n", customer.id, clock, clock - customer.arrival_time);
                total_wait += clock - customer.arrival_time;
            }
        }
    }
    printf("전체 대기 시간 = %d분\n", total_wait);
    return 0;
}