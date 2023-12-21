#include <stdio.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 70
#define MAX_STRING 50

typedef struct user {
    int no;
    char name[MAX_STRING];
    char address[MAX_STRING];
} user;

user stack[MAX_STACK_SIZE];
int top = -1;

int isEmpty();
int isFull();
void push(user item);
user pop();
user peek();

int main() 
{
    user iu = { 20230501,
                "KIM",
                "DAEGU" };
    user ou;

    push(iu);
    ou = pop();

    printf("user_no : %d\n", ou.no);
    printf("user_name : %s\n", ou.name);
    printf("user_address : %s\n", ou.address);
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

void push(user item)
{
    if (is_full())
    {
        fprintf(stderr, "stack full error\n");
        return;
    }
    else
    {
        stack[++top] = item;
    }
}

user pop()
{
    if (is_empty())
    {
        fprintf(stderr, "stack empty error\n");
        exit(1);
    }
    else
    {
        return stack[top--];
    }
}

user peek()
{
    if (is_empty())
    {
        fprintf(stderr, "stack empty error\n");
        exit(1);
    }
    else
    {
        return stack[top];
    }
}