#include <stdio.h>

void insertion_sort(int *arr, int size);
void print_array(int *arr, int size);

/**
 * 시간복잡도: O(n^2)
*/
int main()
{
    int arr[5] = {7, 4, 5, 1, 3};

    printf("Array before sorting: ");
    print_array(arr, 5);

    insertion_sort(arr, 5);
    
    printf("Array after sorting: ");
    print_array(arr, 5);

    return 0;
}

void insertion_sort(int *arr, int size)
{
    
    int i, j;
    for (i = 1; i < size; i++)
    {
        int temp = arr[i];

        for (j = i; j > 0 && arr[j - 1] > temp; j--)
        {
            arr[j] = arr[j - 1]; // 한칸 뒤로 밀기
        }
        arr[j] = temp;
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