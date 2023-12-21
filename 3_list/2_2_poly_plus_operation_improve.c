#include <stdio.h>
#include <stdlib.h>

typedef struct ListNode {
    int coef; // 계수
    int expon; // 지수
    struct ListNode *next;
} ListNode;

typedef struct ListType {
    int size;
    ListNode *head;
    ListNode *tail;
} ListType;

ListNode * insertSortNode(ListNode *head, int coef, int expon);
void polyPrint(ListNode* head);
ListType * create();
void * polyAdd(ListNode *a, ListNode *b, ListType *c);

int main()
{
    ListNode *headA = NULL;
    ListNode *headB = NULL;
    ListType *c = create();
    
    headA = insertSortNode(headA, 3, 12);
    headA = insertSortNode(headA, 4, 12);
    headA = insertSortNode(headA, 2, 9);
    headA = insertSortNode(headA, 1, 0);

    headB = insertSortNode(headB, 3, 12);
    headB = insertSortNode(headB, 6, 8);
    headB = insertSortNode(headB, 4, 2);

    polyPrint(headA);
    polyPrint(headB);
    polyAdd(headA, headB, c);

    polyPrint(c->head);

    return 0;
}

ListType * create()
{
    ListType *plist = (ListType *)malloc(sizeof(ListType));
    plist->size = 0;
    plist->head = plist->tail = NULL;
    return plist;
}
/*
    노드를 생성하여 연결리스트 끝에 삽입합니다.
    시간복잡도: 0(1)
*/
void insertLast(ListType *plist, int coef, int expon)
{
    ListNode *newNode = (ListNode *)malloc(sizeof(ListNode));
    newNode->coef = coef;
    newNode->expon = expon;
    newNode->next = NULL;

    if (plist->tail == NULL)
    {
        plist->head = plist->tail = newNode;
    }
    else
    {
        plist->tail->next = newNode;
        plist->tail = newNode;
    }
    plist->size++;
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

void * polyAdd(ListNode *a, ListNode *b, ListType *c)
{
    int sum;

    while (a && b)
    {
        if (a->expon == b->expon)
        {
            sum = a->coef + b->coef;
            if (sum != 0)
            {
                insertLast(c, sum, a->expon);
            }
            a = a->next;
            b = b->next;
        }
        else if (a->expon > b->expon)
        {
            insertLast(c, a->coef, a->expon);
            a = a->next;
        }
        else
        {
            insertLast(c, b->coef, b->expon);
            b = b->next;
        }
    }

    for (; a != NULL; a = a->next)
    {
        insertLast(c, a->coef, a->expon);
    }
    for (; b != NULL; b = b->next)
    {
        insertLast(c, b->coef, b->expon);
    }
}

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
/*
print result:
    poly = 7x^12 + 2x^9 + 1x^0
    poly = 3x^12 + 6x^8 + 4x^2
    poly = 10x^12 + 2x^9 + 6x^8 + 4x^2 + 1x^0
*/