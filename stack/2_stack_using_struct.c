#include <stdio.h>
#include <stdlib.h>

#define MAX_STACK_SIZE 100

typedef int element;
typedef struct Stack{
    element data[MAX_STACK_SIZE];
    int top;
}Stack;

void initStack(Stack *s);
int isEmpty(Stack *s);
int isFull(Stack *s);
void push(Stack *s, element item);
element pop(Stack *s);
element peek(Stack *s);

/**
 * 구조체를 사용한 스택 예제
*/
int main() 
{
    Stack s;
    
    initStack(&s);
    push(&s, 1);
    push(&s, 2);
    push(&s, 3);
    printf("%d\n", pop(&s));
    printf("%d\n", pop(&s));
    printf("%d\n", pop(&s));
    
    return 0;
}

void initStack(Stack *s)
{
    s->top = -1;
}

int isEmpty(Stack *s)
{
    return (s->top == -1);
}

int isFull(Stack *s)
{
    return (s->top == (MAX_STACK_SIZE - 1));
}

void push(Stack *s, element item)
{
    if (isFull(s))
    {
        fprintf(stderr, "stack full error\n");
        return;
    }

    s->data[++(s->top)] = item;
}

element pop(Stack *s)
{
    if (isEmpty(s))
    {
        fprintf(stderr, "stack empty error\n");
        exit(1);
    }

    return s->data[(s->top)--];
}

element peek(Stack *s)
{
    if (isEmpty(s))
    {
        fprintf(stderr, "stack empty error\n");
        exit(1);
    }
    
    return s->data[s->top];
}