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
    for (int i = 3; i <= n; i++)
    {
        mz[i] = mz[i-1] + mz[i-2];
    }
    
    return mz[n];
}