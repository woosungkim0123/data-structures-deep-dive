#include <stdio.h>
#include <stdlib.h>

typedef struct ListNode {
    int coef; // 계수
    int expon; // 지수
    struct ListNode *next;
} ListNode;

ListNode * insertSortNode(ListNode *head, int coef, int expon);
void polyPrint(ListNode* head);

int main()
{
    ListNode *headA = NULL;
    ListNode *headB = NULL;

    headA = insertSortNode(headA, 3, 12);
    headA = insertSortNode(headA, 4, 12);
    headA = insertSortNode(headA, 2, 9);
    headA = insertSortNode(headA, 1, 0);

    headB = insertSortNode(headB, 3, 12);
    headB = insertSortNode(headB, 6, 8);
    headB = insertSortNode(headB, 4, 2);

    polyPrint(headA);
    polyPrint(headB);
    return 0;
}

/*
    노드를 생성하여 연결리스트 정렬에 맞게 삽입합니다.
    시간복잡도: 0(n)
*/
ListNode * insertSortNode(ListNode *head, int coef, int expon)
{
    ListNode *newNode = (ListNode *) malloc(sizeof(ListNode));
    newNode->coef = coef;
    newNode->expon = expon;
    newNode->next = NULL;

    // 첫 노드인 경우
    if (head == NULL) 
    {
        head = newNode;
        return head;
    }

    // 가장 큰 지수가 들어온 경우
    if (head->expon < expon)
    {
        newNode->next = head;
        head = newNode;
        return head;
    }

    // 가장 큰 지수와 같은 경우, 계수를 더하기
    if (head->expon == newNode->expon)
    {
        head->coef += newNode->coef;
        return head;
    }

    // 일반적인 경우, 지수가 같은 경우 더하기
    ListNode *currentNode = head;
    while (currentNode->next != NULL)
    {   
        // 지수가 같은 경우
        if (currentNode->next->expon == newNode->expon)
        {
            currentNode->next->coef += newNode->coef;
            return head;
        }
        // 지수 사이에 들어가는 경우
        else if (currentNode->next->expon < newNode->expon)
        {
            newNode->next = currentNode->next;
            currentNode->next = newNode;
            return head;
        }
        currentNode = currentNode->next;
    }
    // 가장 작은 지수인 경우
    currentNode->next = newNode;

    return head;
}
/*
void poly_add(ListType* plist1, ListType* plist2, ListType* plist3)
{
    ListNode* a = plist1->head;
    ListNode* b = plist2->head;

    int sum;

    while (a && b)
    {
        if (a->expon == b->expon)
        {
            sum = a->coef + b->coef;
            if (sum != 0)
            {
                insert_last(plist3, sum, a->expon);
            }
            a = a->link;
            b = b->link;
        }
        else if (a->expon > b->expon)
        {
            insert_last(plist3, a->coef, a->expon);
            a = a->link;
        }
        else
        {
            insert_last(plist3, b->coef, b->expon);
            b = b->link;
        }
    }

    for (; a != NULL; a = a->link)
    {
        insert_last(plist3, a->coef, a->expon);
    }
    for (; b != NULL; b = b->link)
    {
        insert_last(plist3, b->coef, b->expon);
    }
}
*/
void polyPrint(ListNode* head)
{
    ListNode* currentNode = head;
    printf("poly = ");
    while (currentNode->next != NULL)
    {
        printf("%dx^%d + ", currentNode->coef, currentNode->expon);
        currentNode = currentNode->next;
    }
    printf("%dx^%d\n", currentNode->coef, currentNode->expon);
}