#include <stdio.h>

int fibo(int n);


int main()
{
    int value = fibo(5);
    printf("value: %d\n", value);

    return 0;
}

// 0(2^n)
int fibo(int n)
{
    if (n == 1 || n == 2)
    {
        return 1;
    }

    return fibo(n-1) + fibo(n-2);
}