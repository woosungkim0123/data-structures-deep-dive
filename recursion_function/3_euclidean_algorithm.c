#include <stdio.h>

typedef int element;

element gcd(element m, element n);

int main()
{
    element value = gcd(72, 30);
    printf("value: %d\n", value);
    return 0;
}
/**
 * 연산이 있는 것이 아닌 return만 하는 재귀함수의 결과값은 무조건 종료조건 입니다.(m)
*/
element gcd(element m, element n)
{
    if (n == 0)
    {
        return m; // 최대 공약수
    }

    return gcd(n, m % n); 
}