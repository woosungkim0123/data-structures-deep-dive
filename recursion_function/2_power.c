#include <stdio.h>

typedef int element;

element power_recursion(element n, element m);

/**
 * 거듭 제곱을 재귀적으로 구하는 함수
*/
int main() 
{
    element value = power_recursion(2, 3);
    printf("value: %d\n", value);

    return 0;
}

element power_recursion(element n, element m)
{
    if (m == 0)
    {
        return 1;
    }

    return n * power_recursion(n, m - 1);
}
