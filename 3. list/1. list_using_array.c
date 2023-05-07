#include <stdio.h>
#include <stdlib.h>
#define MAX_LIST_SIZE 100

typedef int element;
typedef struct {
    element array[MAX_LIST_SIZE];
    int size;
} ArrayList;

void error(char* message)
{
    fprintf(stderr, "%s\n", message);
    exit(1);
}

void init(ArrayList *L)
{
    L->size = 0;
}

int is_full(ArrayList *L)
{
    return L->size == MAX_LIST_SIZE;
}

int is_empty(ArrayList *L)
{
    return L->size == 0;
}

element get_entry(ArrayList *L, int pos)
{
    if(pos < 0 || pos >= L->size)
    {
        error("position error");
    }
    return L->array[pos];
}

void print_list(ArrayList *L)
{
    for(int i = 0; i < L->size; i++)
    {
        printf("%d->", L->array[i]);
    }
    printf("\n");
}

void insert_last(ArrayList *L, element item)
{
    if(L->size >= MAX_LIST_SIZE)
    {
        error("list overflow");
    }
    L->array[L->size++] = item;
}

void insert(ArrayList *L, int pos, element item)
{
    if(!is_full(L) && (pos >= 0) && (pos <= L->size))
    {
        for(int i = (L->size - 1); i >= pos; i--)
        {
            L->array[i + 1] = L->array[i];
        }
        L->array[pos] = item;
        L->size++;    
    }
}

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

int main() 
{
    ArrayList list;
    
    init(&list);
    for(int i = 1; i <= 3; i++)
    {
        insert(&list, 0, 10 * i);
        print_list(&list);
    }
    insert_last(&list, 40);
    print_list(&list);
    delete(&list, 0);
    print_list(&list);

    return 0;
}
