#include <stdio.h>

int mz[100] = {0, 1, 1};

int fibo(int n);

int main()
{
    int value = fibo(5);
    printf("value: %d\n", value);

    return 0;
}

// 0(N)
int fibo(int n)
{
    if (mz[n] != 0)
    {
        return mz[n];
    }

    mz[n] = fibo(n-1) + fibo(n-2);
    return mz[n];
}