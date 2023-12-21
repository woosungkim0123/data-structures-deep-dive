#include <stdio.h>
#include <stdlib.h>

#define MAX_STACK_SIZE 100
typedef int element;
element stack[MAX_STACK_SIZE];
int top = -1;

int isEmpty();
int isFull();
void push(element item);
element pop();
element peek();

int main() 
{
    push(4);
    push(5);
    push(10);
    printf("%d\n", pop());
    printf("%d\n", pop());
    printf("%d\n", pop());
    
    return 0;
}

int isEmpty()
{
    return (top == -1);
}

int isFull()
{
    return (top == (MAX_STACK_SIZE - 1));
}

void push(element item)
{
    if(isFull())
    {
        fprintf(stderr, "stack overflow\n");
        return;
    }
    
    stack[++top] = item;
}

element pop()
{
    if(isEmpty())
    {
        fprintf(stderr, "stack underflow\n");
        exit(1);
    }
    return stack[top--];
}

element peek()
{
    if(isEmpty())
    {
        fprintf(stderr, "stack empty\n");
        exit(1);
    }
    return stack[top];
}

