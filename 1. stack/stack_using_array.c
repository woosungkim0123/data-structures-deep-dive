#include <stdio.h>
#include <stdlib.h>

#define MAX_STACK_SIZE 100
typedef int element;
element stack[MAX_STACK_SIZE];
int top = -1;

int is_empty()
{
    return (top == -1);
}

int is_full()
{
    return (top == (MAX_STACK_SIZE - 1));
}

void push(element item)
{
    if(is_full())
    {
        fprintf(stderr, "stack full error\n");
        return;
    }
    else 
    {
        stack[++top] = item;
    }
}

element pop()
{
    if(is_empty())
    {
        fprintf(stderr, "stack empty error\n");
        exit(1);
    }
    else
    {
        return stack[top--];
    }
}

element peek()
{
    if(is_empty())
    {
        fprintf(stderr, "stack empty error\n");
        exit(1);
    }
    else
    {
        return stack[top];
    }
}

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