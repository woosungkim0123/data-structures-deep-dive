#include <stdio.h>

int fibo(int n);


int main()
{
    int value = fibo(5);
    printf("value: %d\n", value);

    return 0;
}

/**
 * 피보나치 수열을 재귀적으로 구하는 함수
 * 시간복잡도: O(2^n)
*/
int fibo(int n)
{
    if (n == 1 || n == 2)
    {
        return 1;
    }

    return fibo(n-1) + fibo(n-2);
}