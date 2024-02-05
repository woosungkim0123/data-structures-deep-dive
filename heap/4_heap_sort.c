#include <stdio.h>
#include <stdlib.h>

void printHeap(int *arr, int size);
void heapify(int *arr, int size);
void shiftDown(int *arr, int parent, int size);
void heapSort(int *arr, int size);

int main()
{
    int arr[10] = {6, 4, 8, 2, 5, 10, 9, 1, 3, 7};
    
    printf("Before heapSort\n");
    printHeap(arr, 10);

    heapSort(arr, 10);
    
    printf("After heapSort\n");
    printHeap(arr, 10);

    return 0;
}

/**
 * 1. 최대 힙 or 최소 힙을 구성합니다.
 * 2. 루트노드를 마지막 요소와 교환 후 마지막 요소를 제외하고 다시 힙을 구성합니다.
 * - 오름차순의 경우 최대 힙을 사용해서 루트노드(가장 큰 값)을 마지막 요소와 교환하는 방식으로 정렬합니다.
*/
void heapSort(int *arr, int size)
{
    heapify(arr, size);

    // n만큼 반복하면서 힙 정렬
    for (int i = size - 1; i > 0; i--)
    {
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;

        shiftDown(arr, 0, i);
    }
}

void heapify(int *arr, int size)
{   
    int parent = (size / 2) - 1;

    for (int i = parent; i >= 0; i--)
    {
        shiftDown(arr, i, size);
    }
}

void shiftDown(int *arr, int parentIndex, int size)
{
    int leftChildIndex = parentIndex * 2 + 1;
    int rightChildIndex = leftChildIndex + 1;
    int largeIndex = parentIndex;

    // 왼쪽 자식 노드가 부모 노드보다 크면
    if (leftChildIndex < size && arr[leftChildIndex] > arr[largeIndex])
    {
        largeIndex = leftChildIndex;
    }

    // 오른쪽 자식 노드가 부모 노드보다 크면
    if (rightChildIndex < size && arr[rightChildIndex] > arr[largeIndex])
    {
        largeIndex = rightChildIndex;
    }

    if (largeIndex != parentIndex)
    {
        int temp = arr[largeIndex];
        arr[largeIndex] = arr[parentIndex];
        arr[parentIndex] = temp;

        shiftDown(arr, largeIndex, size);
    }
}

void printHeap(int *arr, int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}