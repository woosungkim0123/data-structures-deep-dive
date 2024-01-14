#include <stdio.h>
#include <stdlib.h>

void merge_sort(int *arr, int size);
void merge_sort_util(int *arr, int *arrMerge, int left, int right);
void merge(int *arr, int *arrMerge, int left, int mid, int right);
void print_array(int *arr, int size);

#define ARRAY_SIZE 5

/**
 * 시간복잡도: O(nlogn)
 * 공간복잡도: 0(n) - 정렬된 배열을 담을 공간이 필요함
*/
int main()
{
    int arr[ARRAY_SIZE] = {7, 5, 2, 4, 1};

    printf("Array before sorting: ");
    print_array(arr, ARRAY_SIZE);

    merge_sort(arr, ARRAY_SIZE);
    
    printf("Array after sorting: ");
    print_array(arr, ARRAY_SIZE);

    return 0;
}

void merge_sort(int *arr, int size)
{
    int *arrCopy = (int *)malloc(sizeof(int) * size);
    merge_sort_util(arr, arrCopy, 0, size - 1);
    free(arrCopy);
}

void merge_sort_util(int *arr, int *arrCopy, int left, int right)
{
    int mid;
    
    if (left < right)
    {
        mid = (left + right) / 2;
        merge_sort_util(arr, arrCopy, left, mid);
        merge_sort_util(arr, arrCopy, mid + 1, right);
        merge(arr, arrCopy, left, mid, right);
    }
}

void merge(int *arr, int *arrCopy, int left, int mid, int right)
{
    int index1 = left;
    int index2 = mid + 1;
    int indexM = left;

    // merge 배열 값을 arrCopy에 미리 복사
    for (int i = left; i <= right; i++)
    {
        arrCopy[i] = arr[i];
    }

    while (index1 <= mid && index2 <= right)
    {
        if (arrCopy[index1] < arr[index2])
        {
            arr[indexM++] = arrCopy[index1++];
        }
        else 
        {
            arr[indexM++] = arrCopy[index2++];
        }
    }

    while (index1 <= mid)
    {
        arr[indexM++] = arrCopy[index1++];
    }

    while (index2 <= right)
    {
        arr[indexM++] = arrCopy[index2++];
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