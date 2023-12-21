#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct {
    element* data;
    int capacity;
    int top;
}Stack;

void initStack(Stack* s);
int isEmpty(Stack* s);
int isFull(Stack* s);
void push(Stack* s, element item);
element pop(Stack* s);
element peek(Stack* s);

int main() 
{
    Stack s;
    initStack(&s);

    for (int i = 0; i < 100; i++) {
        push(&s, i);
    }
    for (int i = 0; i < 100; i++) {
        printf("%d\n", pop(&s));
    }
    free(s.data);

    return 0;
}

void initStack(Stack* s)
{
    s->top = -1;
    s->capacity = 1;
    s->data = (element*)malloc(s->capacity * sizeof(element));
}

int isEmpty(Stack* s)
{
    return (s->top == -1);
}

int isFull(Stack* s)
{
    return (s->top == (s->capacity - 1));
}
/*
    가득차면 새로운 배열을 할당하여 복사합니다.
*/
void push(Stack* s, element item)
{
    if (isFull(s))
    {
        s->capacity *= 2;
        s->data = (element*)realloc(s->data, s->capacity * sizeof(element));
    }
    s->data[++(s->top)] = item;
}

element pop(Stack* s)
{
    if (is_empty(s))
    {
        fprintf(stderr, "stack empty error\n");
        exit(1);
    }
    else
    {
        return s->data[(s->top)--];
    }
}

element peek(Stack* s)
{
    if (isEmpty(s))
    {
        fprintf(stderr, "stack empty error\n");
        exit(1);
    }
    else
    {
        return s->data[s->top];
    }
}