#include <stdio.h>

void selection_sort(int *arr, int size);
void print_array(int *arr, int size);

/**
 * 시간복잡도: O(n^2)
*/
int main()
{
    int arr[5] = {7, 4, 5, 1, 3};

    printf("Array before sorting: ");
    print_array(arr, 5);

    selection_sort(arr, 5);
    
    printf("Array after sorting: ");
    print_array(arr, 5);

    return 0;
}

void selection_sort(int *arr, int size)
{
    
    for (int i = 0; i < size - 1; i++)
    {
        int minIndex = i;
        for (int j = i + 1; j < size; j++)
        {
            if (arr[minIndex] > arr[j])
            {
                minIndex = j;
            }
        }
        int temp = arr[i];
        arr[i] = arr[minIndex];
        arr[minIndex] = temp;
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