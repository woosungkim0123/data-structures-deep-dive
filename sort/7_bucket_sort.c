#include <stdio.h>
#include <stdlib.h>

void bucket_sort(int *arr, int size);
void print_array(int *arr, int size);
void quick_sort(int *arr, int left, int right);

#define ARRAY_SIZE 10

/**
 * 버킷 정렬 (퀵 정렬 포함)
*/
int main()
{
    int arr[ARRAY_SIZE] = {86, 32, 27, 12, 49, 21, 62, 89, 71, 87};

    printf("Array before sorting: ");
    print_array(arr, ARRAY_SIZE);

    bucket_sort(arr, ARRAY_SIZE);
    
    printf("Array after sorting: ");
    print_array(arr, ARRAY_SIZE);

    return 0;
}

void bucket_sort(int *arr, int size)
{
    int bucket[ARRAY_SIZE][ARRAY_SIZE];
    int bucket_count[ARRAY_SIZE] = {0}; // calloc 대신 사용
    int i;
    int decimal_bucket_divisor = 10;

    // 버킷에 데이터 삽입
    for (i = 0; i < size; i++)
    {
        int bucket_index =  arr[i] / decimal_bucket_divisor;
        bucket[bucket_index][bucket_count[bucket_index]++] = arr[i];
    }

    // 퀵 정렬
    for (i = 0; i < size; i++)
    {
        if (bucket_count[i] > 0)
        {
            quick_sort(bucket[i], 0, bucket_count[i] - 1);
        }
    }

    // 버킷에서 데이터 꺼내기
    int index = 0;
    for (i = 0; i < size; i++)
    {
        int j;
        for (j = 0; j < bucket_count[i]; j++)
        {
            arr[index++] = bucket[i][j];
        }
    }
}

void quick_sort(int *arr, int left, int right)
{

    int pL = left;
    int pR = right;
    int pivot = arr[(left + right) / 2];
    int temp;

    do 
    {
        while (arr[pL] < pivot) pL++;
        while (arr[pR] > pivot) pR--;

        if (pL <= pR) 
        {
            temp = arr[pL];
            arr[pL] = arr[pR];
            arr[pR] = temp;
            pL++;
            pR--;
        } 
    } while (pL <= pR);

    if (left < pR)
    {
        quick_sort(arr, left, pR);
    }
    if (pL < right)
    {
        quick_sort(arr, pL, right);
    }
}


void print_array(int *arr, int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}