#include <stdio.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 50

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

int check_matching(const char* in)
{
    Stack s;
    int n = strlen(in);
    char ch, open_ch;

    init_stack(&s);

    for (int i = 0; i < n; i++)
    {
        ch = in[i];

        switch (ch)
        {
        case '(': case '[': case '{':
            push(&s, ch);
            break;
        case ')': case ']': case '}':
            if (is_empty(&s))
            {
                return 0;
            }
            else
            {
                open_ch = pop(&s);
                if (
                    (open_ch == '(' && ch != ')') ||
                    (open_ch == '[' && ch != ']') ||
                    (open_ch == '{' && ch != '}'))
                {
                    return 0;
                }
            }
            break;
        }
    }
    if (!is_empty(&s))
    {
        return 0;
    }
    return 1;
}

int main()
{
    char* p = "{ A[(i+1)]=0; }";
    if (check_matching(p))
    {
        printf("%s check success\n", p);
    }
    else
    {
        printf("%s check fail\n", p);
    }
    return 0;
}