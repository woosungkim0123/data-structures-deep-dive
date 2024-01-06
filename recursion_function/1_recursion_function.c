#include <stdio.h>

typedef int element;

void recursive(element n);

int main() 
{
    recursive(3);

    return 0;
}

void recursive(element n)
{
    if (n == 0)
    {
        return;
    }
    printf("recursive call before! %d\n", n);
    recursive(n - 1);
    printf("recursive call after! %d\n", n);
}