#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct Stack 
{
    element value;
    struct Stack *link;
}Stack;

typedef struct {
    Stack *top;
}StackType;

void init(StackType *s);
int isEmpty(StackType *s);
void push(StackType *s, element value);
void printStack(StackType *s);
element pop(StackType *s);

int main() 
{
    StackType *s;
    init(s);

    for (int i = 1; i <= 3; i++) {
        push(s, i);
        printStack(s);
    }
    for (int i = 1; i <= 3; i++) {
        pop(s);
        printStack(s);
    }
    return 0;
}

void init(StackType *s)
{
    s->top = NULL;
}

int isEmpty(StackType *s)
{
    return (s->top == NULL);
}

void push(StackType *s, element value) 
{
    Stack *temp = (Stack *)malloc(sizeof(Stack));
    temp->value = value;
    temp->link = s->top;
    s->top = temp;
}

void printStack(StackType *s)
{
    for (Stack *p = s->top; p != NULL; p = p->link) {
        printf("%d->", p->value);
    }
    printf("NULL \n");
}

element pop(StackType *s)
{
    if (isEmpty(s)) 
    {
        fprintf(stderr, "stack is empty\n");
        exit(1);
    }
    
    Stack *temp = s->top;
    int value = temp->value;
    s->top = s->top->link;
    free(temp);
    return value;
}

/*
print result:
    1->NULL 
    2->1->NULL
    3->2->1->NULL
    2->1->NULL
    1->NULL
    NULL
*/