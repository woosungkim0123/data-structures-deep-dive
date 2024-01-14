#include <stdio.h>
#include <stdlib.h>

void bucket_sort(int *arr, int size, int range);
void print_array(int *arr, int size);

#define ARRAY_SIZE 10

/**
 * n: 데이터 개수, k: 버킷의 수
 * 시간복잡도: 조건이 맞으면 0(n + k)
*/
int main()
{
    int arr[ARRAY_SIZE] = {3, 2, 1, 1, 5, 4, 3, 2, 1, 3};

    printf("Array before sorting: ");
    print_array(arr, ARRAY_SIZE);

    bucket_sort(arr, ARRAY_SIZE, 6); // 5는 배열의 최대값 + 1(인덱스 0은 더미로 사용)
    
    printf("Array after sorting: ");
    print_array(arr, ARRAY_SIZE);

    return 0;
}

void bucket_sort(int *arr, int size, int range)
{
    // calloc 0으로 초기화된 메모리를 할당 (첫번째 인자로 크기)
    int *bucket = (int *)calloc(range, sizeof(int));
    int i, j, index = 0;
    
    for (i = 0; i < size; i++)
    {
        bucket[arr[i]]++;
    }
    // bucket 만큼 돌림 (1 ~ 5 = 5번)
    for (i = 1; i < range; i++)
    {
        // bucket[i] 만큼 돌림 (1이 3개면 3번)
        for (j = 1; j <= bucket[i]; j++)
        {
            arr[index++] = i;
        }
    }
    free(bucket);
}

void print_array(int *arr, int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}