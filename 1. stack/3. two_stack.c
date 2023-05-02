#include <stdio.h>
#include <stdlib.h>

#define MAX_STACK_SIZE 50

typedef int element;
typedef struct {
    element data[MAX_STACK_SIZE];
    int top;
} Stack;

void init_stack(Stack* s)
{
    s->top = -1;
}

int is_empty(Stack* s)
{
    return (s->top == -1);
}

int is_full(Stack* s)
{
    return (s->top == (MAX_STACK_SIZE - 1));
}

void push(Stack* s, element item)
{
    if (is_full(s))
    {
        fprintf(stderr, "stack full error\n");
        return;
    }
    else
    {
        s->data[++(s->top)] = item;
    }
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
    if (is_empty(s))
    {
        fprintf(stderr, "stack empty error\n");
        exit(1);
    }
    else
    {
        return s->data[s->top];
    }
}

int main() {
    Stack s1;
    Stack s2;

    init_stack(&s1);
    init_stack(&s2);

    push(&s1, 1);
    push(&s1, 11);
    push(&s1, 111);
    push(&s2, 2);
    push(&s2, 22);
    push(&s2, 222);

    printf("%d\n", pop(&s1));
    printf("%d\n", pop(&s2));
    printf("%d\n", pop(&s1));
    printf("%d\n", pop(&s2));
    printf("%d\n", pop(&s1));
    printf("%d\n", pop(&s2));

    return 0;
}