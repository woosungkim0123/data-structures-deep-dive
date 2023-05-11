#include <stdio.h>
#include <stdlib.h>

typedef char element[100];
typedef struct ListNode {
    element data;
    struct ListNode* link;
} ListNode;

ListNode* insert_first(ListNode* head, element data)
{
    ListNode* node = (ListNode*)malloc(sizeof(ListNode));
    strcpy(node->data, data);
    if (head == NULL)
    {
        head = node;
        node->link = head;
    }
    else
    {
        node->link = head->link;
        head->link = node;
    }
    return head;
}

int main()
{
    ListNode* head = NULL;

    head = insert_first(head, "KIM");
    head = insert_first(head, "HAN");
    head = insert_first(head, "JO");

    ListNode* p = head;
    for (int i = 0; i < 30; i++)
    {
        printf("current turn : %s \n", p->data);
        p = p->link;
    }
    return 0;
}