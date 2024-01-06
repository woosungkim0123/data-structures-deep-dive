#include <stdio.h>

void tower_of_hanoi(int n, char from, char temp, char to);
int tower_of_hanoi_count(int n);
int tower_of_hanoi_count_use_math(int n);

int main()
{
    tower_of_hanoi(3, 'A', 'B', 'C');

    int value = tower_of_hanoi_count(3);
    printf("value: %d\n", value);

    int value2 = tower_of_hanoi_count_use_math(3);
    printf("value2: %d\n", value2);

    return 0;
}

void tower_of_hanoi(int n, char from, char temp, char to)
{
    if (n == 1)
    {
        printf("%c => %c\n", from, to);
        return;
    }

    tower_of_hanoi(n-1, from, to, temp); // 출발지에서 임시로
    printf("%c => %c\n", from, to);
    tower_of_hanoi(n-1, temp, from, to); // 임시에서 목적지로
}

int tower_of_hanoi_count(int n)
{
    if (n == 1)
    {
        return 1;
    }

    return 1 + 2 * tower_of_hanoi_count(n-1);
}

int tower_of_hanoi_count_use_math(int n)
{
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += (1 << i);
    }
    return sum;
}