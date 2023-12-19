#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct StackNode {
    element data;
    struct StackNode *link;
} StackNode;

typedef struct {
    StackNode *top;
} LinkedStackType;

void init(LinkedStackType *s)
{
    s->top = NULL;
}

int is_empty(LinkedStackType *s)
{
    return (s->top == NULL);
}

void push(LinkedStackType *s, element item) 
{
    StackNode *temp = (StackNode *)malloc(sizeof(StackNode));
    temp->data = item;
    temp->link = s->top;
    s->top = temp;
}

void print_stack(LinkedStackType *s)
{
    for (StackNode *p = s->top; p != NULL; p = p->link) {
        printf("%d->", p->data);
    }
    printf("NULL \n");
}

element pop(LinkedStackType *s)
{
    if(is_empty(s)) {
        fprintf(stderr, "stack is empty\n");
        exit(1);
    }
    else {
        StackNode *temp = s->top;
        int data = temp->data;
        s->top = s->top->link;
        free(temp);
        return data;
    }
}

int main() 
{
    LinkedStackType s;
    init(&s);
    for (int i = 1; i <= 3; i++) {
        push(&s, i);
        print_stack(&s);
    }
    for (int i = 1; i <= 3; i++) {
        pop(&s);
        print_stack(&s);
    }
    return 0;
}