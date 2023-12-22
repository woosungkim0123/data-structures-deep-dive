#include <stdio.h>
#include <stdlib.h>

typedef int element;
typedef struct ListNode 
{
    element value;
    struct ListNode* prev;
    struct ListNode* next;
}ListNode;

ListNode * insertFrontNode(ListNode *head, element value);
ListNode * insertTailNode(ListNode *head, element value);
ListNode * removeFrontNode(ListNode *head);
ListNode * removeTailNode(ListNode *head);
ListNode * reverse(ListNode *head);
void printList(ListNode *head);

int main()
{
    ListNode *head = NULL;

    for (int i = 1; i <= 10; i++)
    {
        head = insertFrontNode(head, i);
    }
    head = insertTailNode(head, 100);
    head = insertTailNode(head, 200);

    printList(head);

    head = reverse(head);

    printList(head);

    return 0;
}

/*
    노드를 생성하여 연결리스트 맨 앞에 삽입합니다.
    시간복잡도: 0(1)
*/
ListNode * insertFrontNode(ListNode *head, element value)
{
    ListNode *newNode = (ListNode *) malloc(sizeof(ListNode)); // 노드 생성
    newNode->value = value;
    newNode->prev = NULL;
    newNode->next = NULL;

    if (head == NULL) // 생성된 노드가 없는 경우(첫 노드)
    {
        head = newNode;
        return head;
    }

    head->prev = newNode;
    newNode->next = head;
    head = newNode;
    
    return head;
}

/*
    노드를 생성하여 연결리스트 맨 뒤에 삽입합니다.
    시간복잡도: 0(n)
*/
ListNode * insertTailNode(ListNode *head, element value)
{
    ListNode *currentNode = head;
    ListNode *newNode;
    newNode = (ListNode *) malloc(sizeof(ListNode));
    newNode->value = value;
    newNode->prev = NULL;
    newNode->next = NULL;

    if (head == NULL) // 연결리스트 구성 되기 전
    {
        head = newNode;
        return head;
    }

    // 맨 뒤에 넣으려면 노드를 순회하는 작업이 필요함
    while(currentNode->next != NULL)
    {
        currentNode = currentNode->next;
    }
    newNode->prev = currentNode;
    currentNode->next = newNode;
    
    return head;
}

// 연결리스트를 출력합니다.
void printList(ListNode *head)
{
    ListNode * currentNode = head;
    while (currentNode->next != NULL)
    {
        printf("%d->", currentNode->value);
        currentNode = currentNode->next;
    }
    printf("%d\n", currentNode->value);
}

/*
    노드의 순서를 반대로 뒤집습니다.
    시간복잡도: 0(n)
*/
ListNode * reverse(ListNode *head)
{
    ListNode *currentNode = head;
    ListNode *tempNode;

    // 노드가 0개 또는 1개인 경우 뒤집을 필요가 없다.
    if (head == NULL || head->next == NULL)
    {
        return head;
    }

    while (currentNode != NULL)
    {
        tempNode = currentNode->next;
        currentNode->next = currentNode->prev;
        currentNode->prev = tempNode;

        if (currentNode->prev == NULL)
        {
            head = currentNode;
            return head;
        }

        currentNode = currentNode->prev;    
    }

    return head;
}