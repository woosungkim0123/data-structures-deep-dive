#include <stdio.h>

void bubble_sort(int *arr, int size);
void print_array(int *arr, int size);

/**
 * 시간복잡도: O(n^2)
*/
int main()
{
    int arr[5] = {7, 4, 5, 1, 3};

    printf("Array before sorting: ");
    print_array(arr, 5);

    bubble_sort(arr, 5);
    
    printf("Array after sorting: ");
    print_array(arr, 5);

    return 0;
}

void bubble_sort(int *arr, int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = 0; j < (size - 1 - i); j++)
        {
            if (arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
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