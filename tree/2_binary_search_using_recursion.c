#include <stdio.h>

#define ARRAY_SIZE 10

int binary_search(int arr[], int start, int end, int search_value);


/**
 * 재귀를 이용한 이진 탐색
*/

int main()
{
    int arr[ARRAY_SIZE] = {1, 2, 3, 4, 5, 6, 7, 8 , 9, 10};
    int index;
    int search_value = 7;

    index = binary_search(arr, 0, ARRAY_SIZE - 1, search_value);
    
    if (index == -1) {
        printf("Not found.\n");
    }
    else {
        printf("Found. index is %d\n", index);
    }


    return 0;
}

int binary_search(int *arr, int start, int end, int target)
{
    if(start > end) 
    {
        return -1;
    }

    int mid = (start + end) / 2;

    if(arr[mid] == target) 
    {
        return mid;
    }

    if(arr[mid] > target) 
    {
        return binary_search(arr, start, mid - 1, target);
    }
    else 
    {
        return binary_search(arr, mid + 1, end, target);
    }
}