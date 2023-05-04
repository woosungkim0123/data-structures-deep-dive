#include <stdio.h>
#include <stdlib.h>

#define MAX_STACK_SIZE 100

typedef char element;
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

int eval(char exp[])
{
    Stack s;
    int n = strlen(exp);
    int op1, op2, value;
    char ch;

    init_stack(&s);

    for (int i = 0; i < n; i++)
    {
        ch = exp[i];
        if (ch != '+' && ch != '-' && ch != '*' && ch != '/')
        {
            value = ch - '0';
            push(&s, value);
        }
        else
        {
            op2 = pop(&s);
            op1 = pop(&s);
            switch (ch)
            {
            case '+': push(&s, op1 + op2); break;
            case '-': push(&s, op1 - op2); break;
            case '*': push(&s, op1 * op2); break;
            case '/': push(&s, op1 / op2); break;
            }
        }
    }
    return pop(&s);
}

int main()
{
    int result;
    result = eval("82/3-32*+");
    printf("%d\n", result);
    return 0;
}