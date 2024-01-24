#include <stdio.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 70
#define MAX_STRING 50

typedef struct User 
{
    int no;
    char name[MAX_STRING];
    char address[MAX_STRING];
}User;

User stack[MAX_STACK_SIZE];
int top = -1;

int isEmpty();
int isFull();
void push(User item);
User pop();
User peek();

int main() 
{
    User iu = { 20230501,
                "KIM",
                "DAEGU" };
    User ou;

    push(iu);
    ou = pop();

    printf("User_no : %d\n", ou.no);
    printf("User_name : %s\n", ou.name);
    printf("User_address : %s\n", ou.address);
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

void push(User item)
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

User pop()
{
    if (isEmpty())
    {
        fprintf(stderr, "stack empty error\n");
        exit(1);
    }
    else
    {
        return stack[top--];
    }
}

User peek()
{
    if (isEmpty())
    {
        fprintf(stderr, "stack empty error\n");
        exit(1);
    }
    else
    {
        return stack[top];
    }
}