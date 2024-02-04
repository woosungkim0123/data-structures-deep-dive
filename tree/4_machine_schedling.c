#include <stdio.h>

#define MAX_ELEMENT 200

typedef struct {
    int id;
    int avail;
}element;

typedef struct {
    element heap[MAX_ELEMENT];
    int heapSize;
}HeapType;

void init(HeapType *h);
HeapType * create();



int main()
{
    HeapType heap;
    init(&heap);
    return 0;
}

HeapType * create()
{
    return (HeapType *)malloc(sizeof(HeapType));
}

void init(HeapType *h)
{
    h->heapSize = 0;
}
