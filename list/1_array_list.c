#include <stdio.h>
#include <stdlib.h>

#pragma warning (disable : 4996)

#define MAX_LIST_SIZE 2
#define INCREASE_FACTOR 2

typedef int element;
typedef struct ArrayList {
    element *array;
    int size;
    int capacity;
}ArrayList;

void error(char *message);
void init(ArrayList *L);
int isFull(ArrayList *L);
int isEmpty(ArrayList *L);
element get_entry(ArrayList *L, int pos);
void printList(ArrayList *L);
void insertLast(ArrayList *L, element item);
void insert(ArrayList *L, int pos, element item);
element delete(ArrayList *L, int pos);
void expandArray(ArrayList *L);

/*
    배열을 이용하여 리스트를 구현 (+ 동적 배열) - 출력 결과 최하단 참고
*/
int main() 
{
    ArrayList list;
    init(&list);

    for(int i = 1; i <= 3; i++)
    {
        insert(&list, 0, 10 * i);
        printList(&list);
    }
    insertLast(&list, 40);
    printList(&list);
    
    delete(&list, 0);
    printList(&list);

    return 0;
}

void error(char *message)
{
    fprintf(stderr, "%s\n", message);
    exit(1);
}

// 리스트 초기화
void init(ArrayList *L)
{
    L->size = 0;
    L->capacity = MAX_LIST_SIZE;
    L->array = (element *)malloc(L->capacity * sizeof(element));
    if (L->array == NULL)
    {
        error("Failed to allocate array");
    }
}

int isFull(ArrayList *L)
{
    return L->size == MAX_LIST_SIZE;
}

int isEmpty(ArrayList *L)
{
    return L->size == 0;
}

/*
    리스트의 pos 위치에 있는 요소를 반환
    시간복잡도: O(1)
*/
element get_entry(ArrayList *L, int pos)
{
    if(pos < 0 || pos >= L->size)
    {
        error("position error");
    }
    return L->array[pos];
}

// 리스트 전체 출력
void printList(ArrayList *L)
{
    for(int i = 0; i < L->size; i++)
    {
        printf("%d->", L->array[i]);
    }
    printf("\n");
}

/*
    리스트의 마지막에 요소를 추가
    시간복잡도: O(1)
*/
void insertLast(ArrayList *L, element item)
{
    expandArray(L);
    L->array[L->size++] = item;
}

/*
    리스트의 특정 위치에 요소를 추가
    시간복잡도: O(n)
*/
void insert(ArrayList *L, int pos, element item)
{
    if (pos < 0 || pos > L->size)
    {
        error("Invalid position");
    }

    // 배열이 가득찬지 확인하고, 필요하면 확장
    expandArray(L);

    // 삽입할 위치부터 마지막 요소까지 한 칸씩 뒤로 이동
    for(int i = (L->size - 1); i >= pos; i--)
    {
        L->array[i + 1] = L->array[i];
    }

    // 새 요소 삽입
    L->array[pos] = item;
    L->size++;    
}

/*
    리스트의 pos 위치에 있는 요소를 삭제
    삭제할 위치에 있는 요소부터 끝까지 한 칸씩 앞으로 이동
    시간복잡도: O(n)
*/
element delete(ArrayList *L, int pos)
{
    element item;
    
    if(pos < 0 || pos >= L->size)
    {
        error("position error");
    }
    item = L->array[pos];
    
    for(int i = pos; i < (L->size - 1); i++)
    {
        L->array[i] = L->array[i + 1];
    }
    L->size--;
    return item;
}

// 배열 확장
void expandArray(ArrayList *L)
{
    if (L->size >= L->capacity)
    {
        int newCapacity = L->capacity * INCREASE_FACTOR;

        element *newArray = (element *) realloc(L->array, newCapacity * sizeof(element));
        if (newArray == NULL)
        {
            error("Failed to expand array");
        }
        printf("Array expanded to %d elements.\n", newCapacity);
        L->array = newArray;
        L->capacity = newCapacity;
    }
}

/*
print result:
    10->
    20->10->
    Array expanded to 4 elements.
    30->20->10->
    30->20->10->40->
    20->10->40->
*/