#include <stdio.h>

typedef int element;
typedef struct {
    element data;
    struct ListNode* link;
} ListNode;

int main()
{
    ListNode* head = NULL;
    head = (ListNode*)malloc(sizeof(ListNode));
    head->data = 10;
    head->link = NULL;

    ListNode* p = NULL;
    p = (ListNode*)malloc(sizeof(ListNode));
    p->data = 20;
    p->link = NULL;

    head->link = p;

    return 0;
}
