#include <stdio.h>
#include <stdlib.h>

#define MAX_ELEMENT 200

typedef struct {
    int id;
    int avail; // 기계가 사용 가능하게 되는 시간
}element;

typedef struct {
    element arr[MAX_ELEMENT];
    int size;
} Heap;

Heap * createHeap();
void init(Heap *heap);
element extractMin(Heap *heap);
void insertMinHeap(Heap *heap, element value);
void shiftUp(Heap *heap, int childIndex);
void shiftDown(Heap *heap, int parentIndex);

#define JOBS 7
#define MACHINES 3

int main()
{
    int jobs[JOBS] = {8, 7, 6, 5, 3, 2, 1}; // 작업은 정렬되어 있는 상태
    Heap *h;
    element machine = {0, 0};

    h = createHeap();
    init(h);

    for (int i = 0; i < 3; i++)
    {
        machine.id = i + 1;
        machine.avail = 0;
        insertMinHeap(h, machine);
    }

    // 최소 히프에서 기계를 꺼내어 작업을 할당하고 사용가능 시간을 갱신 후 추가
    for (int i = 0; i < JOBS; i++)
    {
        machine = extractMin(h);
        printf("JOB %d:: %d Hour ~ %d Hour Machine %d\n", i, machine.avail, machine.avail + jobs[i], machine.id);
        machine.avail += jobs[i];
        insertMinHeap(h, machine);
    }

    return 0;
}

Heap * createHeap()
{
    return (Heap *)malloc(sizeof(Heap));
}

void init(Heap *heap)
{
    heap->size = 0;
}

void insertMinHeap(Heap *heap, element value)
{
    if (heap->size == MAX_ELEMENT) // 더이상 원소를 저장할 수 없음
    {
        printf("Heap is full\n");
        return;
    }

    heap->arr[heap->size] = value;
    
    // 힙구조 만들기 (최소 힙) - shift up - 부모노드와 비교하여 자식노드가 더 크면 교환
    shiftUp(heap, heap->size);

    heap->size++;
}

element extractMin(Heap *heap)
{
    if (heap->size == 0)
    {
        printf("Heap is empty\n");
        element e = {-1, -1};
        return e;
    }
    element min = heap->arr[0];

    heap->arr[0] = heap->arr[heap->size - 1];
    heap->size--;

    // 힙구조 만들기 (최소 힙) - shift down - 자식노드와 비교하여 부모노드가 더 작으면 교환
    shiftDown(heap, 0);

    return min;
}

void shiftUp(Heap *heap, int childIndex) 
{
    int parentIndex = (childIndex - 1) / 2;

    if (parentIndex >= 0 && heap->arr[parentIndex].avail > heap->arr[childIndex].avail) 
    {
        element temp = heap->arr[parentIndex];
        heap->arr[parentIndex] = heap->arr[childIndex];
        heap->arr[childIndex] = temp;

        shiftUp(heap, parentIndex);
    }
}

void shiftDown(Heap *heap, int parentIndex) 
{
    int leftChildIndex = parentIndex * 2 + 1;
    int rightChildIndex = leftChildIndex + 1;
    int smallIndex = parentIndex; // 기본값을 parentIndex로 설정

    if (leftChildIndex < heap->size && heap->arr[leftChildIndex].avail < heap->arr[smallIndex].avail)
    {
        smallIndex = leftChildIndex;
    }

    if (rightChildIndex < heap->size && heap->arr[rightChildIndex].avail < heap->arr[smallIndex].avail) 
    {
        smallIndex = rightChildIndex;
    }

    if (smallIndex != parentIndex) 
    {
        element temp = heap->arr[smallIndex];
        heap->arr[smallIndex] = heap->arr[parentIndex];
        heap->arr[parentIndex] = temp;

        shiftDown(heap, smallIndex);
    }
}