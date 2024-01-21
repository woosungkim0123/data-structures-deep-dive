#include <stdio.h>
#include <stdlib.h>

typedef struct Heap {
    int *arr; // 힙 메모리의 주소를 저장
    int size; // 저장된 원소의 개수
    int capacity;  // 최대 저장 가능한 원소의 개수
} Heap;

void createHeap(Heap *heap, int capacity);
void addHeap(Heap *heap, int data);
void shiftUp(int *arr, int cidx);
void printHeap(Heap *heap);


/**
 * 최대 힙
*/
int main()
{
    Heap heap;

    createHeap(&heap, 10);
    
    addHeap(&heap, 57);
    addHeap(&heap, 32);
    addHeap(&heap, 48);
    addHeap(&heap, 10);
    addHeap(&heap, 15);
    addHeap(&heap, 25);
    addHeap(&heap, 20);
    addHeap(&heap, 9);

    printHeap(&heap);

    addHeap(&heap, 60);

    printHeap(&heap);
    
    return 0;
}

void createHeap(Heap *heap, int capacity)
{
    heap->arr = (int *)malloc(sizeof(int) * capacity);
    heap->size = 0;
    heap->capacity = capacity;
}

void addHeap(Heap *heap, int value)
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

void shiftUp(int *arr, int childIndex)
{
    // 부모노드 = (해당 노드 인덱스 - 1) / 2 
    int parentIndex = (childIndex - 1) / 2;

    // 루트노드까지 올라오면 0 - 1 / 2 = 0.5
    if (parentIndex >= 0 && arr[parentIndex] < arr[childIndex])
    {
        int temp = arr[parentIndex];
        arr[parentIndex] = arr[childIndex];
        arr[childIndex] = temp;

        shiftUp(arr, parentIndex);
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