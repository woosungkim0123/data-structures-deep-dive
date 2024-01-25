#include <stdio.h>
#include <stdlib.h>


typedef struct Node {
    int value;
    struct Node *next;
} Node;

typedef struct HashTable {
    int size;
    Node **head;
} HashTable;

void hashInit(HashTable *pHt, int size);
int hashFunction(int key, int size);
void hashAdd(HashTable *pHt, int key);
void hashDisplay(HashTable *pHt);
int hashFind(HashTable *pHt, int target);
void memoryFree(HashTable *pHt);
int hashRemove(HashTable *pHt, int target);

int main()
{
    HashTable ht;
    hashInit(&ht, 7); // 해시 테이블 크기를 소수로 해야 중복되는 해시 값이 적어진다.

    hashAdd(&ht, 77); //해시테이블, 키값
	hashAdd(&ht, 7);
	hashAdd(&ht, 36);
	hashAdd(&ht, 92);
	hashAdd(&ht, 15);
	hashAdd(&ht, 23);
	hashAdd(&ht, 18);
	hashAdd(&ht, 96);
	hashAdd(&ht, 12);	
	hashAdd(&ht, 69);

	hashDisplay(&ht);

    if (hashFind(&ht, 77))
    {
        printf("77 exist.\n");
    }
    else
    {
        printf("77 not exist \n");
    }

    hashRemove(&ht, 77);

    if (hashFind(&ht, 77))
    {
        printf("77 exist.\n");
    }
    else
    {
        printf("77 not exist \n");
    }
    
    memoryFree(&ht);

    return 0;
}

void hashInit(HashTable *pHt, int size)
{
    pHt->size = size;
    pHt->head = (Node **)calloc(size, sizeof(Node *)); // 포인터가 0이면 가르키는 주소가 없다는 의미
}

void hashAdd(HashTable *pHt, int key)
{
    int hashValue = hashFunction(key, pHt->size);

    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->value = key;
    newNode->next = NULL;

    if (pHt->head[hashValue] == NULL) // 해당 인덱스에 아무것도 없으면
    {
        pHt->head[hashValue] = newNode;
    }
    else // 해당 인덱스에 노드가 있으면
    {
        newNode->next = pHt->head[hashValue];
        pHt->head[hashValue] = newNode;  
    }
}

int hashRemove(HashTable *pHt, int target)
{
	int hashValue = hashFunction(target, pHt->size);

	Node *curNode; 
    Node *delNode;

	if (pHt->head[hashValue] == NULL)
    {
        return 0; //삭제 실패
    }

	curNode = pHt->head[hashValue];

	//삭제할 노드가 첫 노드인 경우
	if (curNode->value == target)
	{
		pHt->head[hashValue] = curNode->next; // head 변경
		free(curNode);
		return 1; //삭제 성공
	}

	//일반적인 경우의 삭제(마지막 노드 포함)
	while (curNode-> next)
	{
		delNode = curNode->next;
		
		if (delNode->value == target)
		{
			curNode->next = delNode->next; // 삭제할 노드의 이전 노드의 next를 삭제할 노드의 next로 변경
			free(delNode);
			return 1; //삭제 성공
		}
		curNode = curNode->next;
	}
	
	return 0;
}

/**
 * 해시 함수
 * - 해시 테이블의 인덱스로 사용할 값을 반환하는 함수
*/
int hashFunction(int key, int size)
{
    return key % size;
}

void hashDisplay(HashTable *pHt)
{
    Node *curNode;

    for (int i = 0; i < pHt->size; i++)
    {
        curNode = pHt->head[i];

        printf("head[%d] hash value => ", i);
        while (curNode)
        {
            printf("%d ", curNode->value);
            curNode = curNode->next;
        }
        puts("");
    }
}

int hashFind(HashTable *pHt, int target)
{
	Node *curNode;
	int hashValue = hashFunction(target, pHt->size);

	curNode = pHt->head[hashValue];

	while (curNode)
	{
		if (curNode->value == target)
        {
            return 1;
        }
		curNode = curNode->next;
	}
	return 0;
}

void memoryFree(HashTable *pHt)
{
	Node *delNode;
	
	//첫 노드 제거(반복)
	for (int i = 0; i < pHt->size; i++)
	{
		while (pHt->head[i] != NULL)
		{
			delNode = pHt->head[i]; //첫 노드를 삭제할 노드로 지정
			pHt->head[i] = pHt->head[i]->next; //head를 변경
			free(delNode);
		}
	}

	free(pHt->head); // 해시 테이블로 사용한 포인터 배열 제거 
}