#include <stdio.h>
#include <stdlib.h>

void printHeap(int *arr, int size);
void heapify(int *arr, int size);
void shiftDown(int *arr, int parent, int size);

/**
 * 최대 힙으로 만들기
*/
int main()
{
    int arr[10] = {6, 4, 8, 2, 5, 7, 9, 1, 3, 10};
    
    printf("Before heapify\n");
    printHeap(arr, 10);

    heapify(arr, 10);
    
    printf("After heapify\n");
    printHeap(arr, 10);

    return 0;
}

/**
 * 최대 힙으로 만들기
 * - 자식 노드가 있는 노드들을 대상으로 자식과 비교하여 자식이 더 크면 교환
*/
void heapify(int *arr, int size)
{   
    // 완전 이진 트리 부모 노드의 개수 = (전체 개수 / 2)
    int parent = (size / 2) - 1; // -1을 해주는 이유는 배열의 인덱스가 0부터 시작하기 때문에

    for (int i = parent; i >= 0; i--)
    {
        shiftDown(arr, i, size); // 부모 노드의 값을 자식 노드의 값과 비교;
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