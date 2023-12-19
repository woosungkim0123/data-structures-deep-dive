#include <stdio.h>
#include <stdlib.h>

#pragma warning (disable : 4996)

typedef int element;
typedef struct ListNode {
    element value;
    struct ListNode *next;
} ListNode;

ListNode * insertFrontNode(ListNode *head, element value);
ListNode * insertTailNode(ListNode *head, element value);
ListNode * removeFrontNode(ListNode *head);
ListNode * removeTailNode(ListNode *head);
ListNode * removeNodeValue(ListNode *head, element value);
void printList(ListNode *head);
int getNodeCount(ListNode* head);
void memoryFree(ListNode *head);

// ListNode* delete_first(ListNode* head);
// ListNode* delete(ListNode* head, ListNode* pre);
/*
    단일 연결리스트
*/
int main()
{
    ListNode *head = NULL;

    for (int i = 1; i <= 10; i++)
    {
        head = insertFrontNode(head, i);
    }

    printList(head);
    printf("count :: %d\n", getNodeCount(head));

    head = removeFrontNode(head);
    printList(head);

    head = insertTailNode(head, 100);
    printList(head);

    head = insertTailNode(head, 200);
    printList(head);

    head = removeTailNode(head);
    printList(head);

    head = removeNodeValue(head, 5);
    printList(head);

    memoryFree(head);
    head = NULL;
    return 0;
}

/*
    노드를 생성하여 연결리스트 맨 앞에 삽입합니다.
    시간복잡도: 0(1)
*/
ListNode * insertFrontNode(ListNode *head, element value)
{
    ListNode *newNode; // 포인터 변수 (8바이트) - 주소를 저장하는 공간만 생김
    newNode = (ListNode *)malloc(sizeof(ListNode)); // 노드 생성
    newNode->value = value;
    newNode->next = NULL;

    if (head == NULL) // 생성된 노드가 없는 경우(첫 노드)
    {
        head = newNode;
        return head;
    }

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
    newNode = (ListNode *)malloc(sizeof(ListNode));
    newNode->value = value;
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
    currentNode->next = newNode;

    return head;
}
/*
    연결리스트 맨 앞의 노드를 제거합니다.
    시간복잡도: 0(1)
*/
ListNode * removeFrontNode(ListNode *head)
{
    ListNode *removedNode = head;
    head = removedNode->next;
    free(removedNode);
    return head;
}

/*
    연결리스트 맨 뒤의 노드를 제거합니다.
    시간복잡도: 0(n)
*/
ListNode * removeTailNode(ListNode *head)
{
    ListNode *currentNode = head;
    ListNode *removedNode;
    if (currentNode->next == NULL) // 노드가 1개인 경우
    {
        free(currentNode);
        return NULL;
    }

    while (currentNode->next->next != NULL)
    {
        currentNode = currentNode->next;
    }
    currentNode->next = NULL;
    free(currentNode->next);

    return head;
}

/*
    특정 값 삭제
    시간복잡도: 0(n)
*/
ListNode * removeNodeValue(ListNode *head, element value)
{
    ListNode *currentNode;
    ListNode *removedNode;

    if (head->value == value)
    {
        removedNode = head;
        head = removedNode->next;
        free(removedNode);
        return head;
    }

    currentNode = head;

    while (currentNode->next != NULL)
    {
        if (currentNode->next->value == value)
        {   
            removedNode = currentNode->next;
            currentNode->next = removedNode->next;
            free(removedNode);
            break;
        }
        currentNode = currentNode->next;
    }
    
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

// 총 노드 개수를 구합니다.
int getNodeCount(ListNode *head)
{
    ListNode* current = head;
    int count = 0;
    while (current != NULL)
    {
        ++count;
        current = current->next;
    }
    return count;
}

// 연결리스트의 전체 메모리를 해제합니다.
void memoryFree(ListNode *head)
{
    while (head != NULL)
    {
        ListNode *removedNode = head;
        head = removedNode->next;
        free(removedNode);
    }
}

/*
print result:
    10->9->8->7->6->5->4->3->2->1
    count :: 10
    9->8->7->6->5->4->3->2->1
    9->8->7->6->5->4->3->2->1->100
    9->8->7->6->5->4->3->2->1->100->200
    9->8->7->6->5->4->3->2->1->100
    9->8->7->6->4->3->2->1->100
*/