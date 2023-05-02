#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct {
    element* data;
    int capacity;
    int top;
}Stack;

void init_stack(Stack* s)
{
    s->top = -1;
    s->capacity = 1;
    s->data = (element*)malloc(s->capacity * sizeof(element));
}

int is_empty(Stack* s)
{
    return (s->top == -1);
}

int is_full(Stack* s)
{
    return (s->top == (s->capacity - 1));
}

void push(Stack* s, element item)
{
    if (is_full(s))
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
    Stack s;
    init_stack(&s);

    for (int i = 0; i < 100; i++) {
        push(&s, i);
    }
    for (int i = 0; i < 100; i++) {
        printf("%d\n", pop(&s));
    }
    free(s.data);

    return 0;
}
