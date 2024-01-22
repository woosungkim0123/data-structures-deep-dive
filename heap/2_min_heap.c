#include <stdio.h>
#include <stdlib.h>

typedef struct Heap {
    int *arr;
    int size;
    int capacity;
} Heap;

void init(Heap *heap, int capacity);
void insert(Heap *heap, int data);
void shiftUp(int *arr, int cidx);
void printHeap(Heap *heap);
void extractMin(Heap *heap);
int findMin(Heap *heap);
void shiftDown(int *arr, int parentIndex, int size);

/**
 * 최소 힙
*/
int main()
{
    Heap heap;

    init(&heap, 10);
    
    insert(&heap, 57);
    insert(&heap, 32);
    insert(&heap, 48);
    insert(&heap, 10);
    insert(&heap, 15);
    insert(&heap, 25);
    insert(&heap, 20);
    insert(&heap, 9);

    printHeap(&heap);

    insert(&heap, 3);

    printHeap(&heap);
    
    int min1 = findMin(&heap);
    printf("min: %d\n", min1);

    extractMin(&heap);

    int min2 = findMin(&heap);
    printf("min: %d\n", min2);
    
    printHeap(&heap);

    return 0;
}

void init(Heap *heap, int capacity)
{
    heap->arr = (int *)malloc(sizeof(int) * capacity);
    heap->size = 0;
    heap->capacity = capacity;
}

void insert(Heap *heap, int value)
{
    if (heap->size == heap->capacity) // 더이상 원소를 저장할 수 없음
    {
        printf("Heap is full\n");
        return;
    }

    heap->arr[heap->size] = value;
    
    // 힙구조 만들기 (최대 힙) - shift up - 부모노드와 비교하여 자식노드가 더 크면 교환
    shiftUp(heap->arr, heap->size);

    heap->size++;
}

void extractMin(Heap *heap)
{
    if (heap->size == 0)
    {
        printf("Heap is empty\n");
        return;
    }

    heap->arr[0] = heap->arr[heap->size - 1];
    heap->size--;

    // 힙구조 만들기 (최대 힙) - shift down - 자식노드와 비교하여 부모노드가 더 작으면 교환
    shiftDown(heap->arr, 0, heap->size);
}

void shiftUp(int *arr, int childIndex)
{
    // 부모노드 = (해당 노드 인덱스 - 1) / 2 
    int parentIndex = (childIndex - 1) / 2;

    // 루트노드까지 올라오면 0 - 1 / 2 = 0.5
    if (parentIndex >= 0 && arr[parentIndex] > arr[childIndex])
    {
        int temp = arr[parentIndex];
        arr[parentIndex] = arr[childIndex];
        arr[childIndex] = temp;

        shiftUp(arr, parentIndex);
    }
}

int findMin(Heap *heap)
{
    return heap->arr[0];
}

void shiftDown(int *arr, int parentIndex, int size)
{
    int leftChildIndex = parentIndex * 2 + 1;
    int rightChildIndex = leftChildIndex + 1;
    int smallIndex = -1; // 배열의 인덱스로 사용할 수 없는 값으로 초기화

    if (leftChildIndex < size) 
    {
        smallIndex = leftChildIndex;
    }

    if (rightChildIndex < size && arr[rightChildIndex] < arr[smallIndex]) 
    {
        smallIndex = rightChildIndex;
    }

    if (smallIndex != -1 && arr[smallIndex] < arr[parentIndex])
    {
        int temp = arr[smallIndex];
        arr[smallIndex] = arr[parentIndex];
        arr[parentIndex] = temp;

        shiftDown(arr, smallIndex, size);
    }
}

void printHeap(Heap *heap)
{
    for (int i = 0; i < heap->size; i++)
    {
        printf("%d ", heap->arr[i]);
    }
    printf("\n");
}

