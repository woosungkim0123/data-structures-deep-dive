#include <stdio.h>

void quick_sort(int *arr, int left, int right);
void print_array(int *arr, int size);

#define ARRAY_SIZE 9

/**
 * 시간복잡도: 최악의 경우 O(n^2), 평균적으로 O(nlogn)
*/
int main()
{
    int arr[ARRAY_SIZE] = {4, 1, 6, 5, 5, 3, 7, 2, 8};

    printf("Array before sorting: ");
    print_array(arr, ARRAY_SIZE);

    quick_sort(arr, 0, ARRAY_SIZE);
    
    printf("Array after sorting: ");
    print_array(arr, ARRAY_SIZE);

    return 0;
}

void quick_sort(int *arr, int left, int right)
{

    int pL = left;
    int pR = right;
    int pivot = arr[(left + right) / 2]; // 중간값을 피벗을 잡음
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

    // 원소가 하나 남은 순간 재귀 종료
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